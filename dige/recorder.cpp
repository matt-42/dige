// Copyright (C) 2010 Matthieu Garrigues
//
// This file is part of dige.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <iostream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavcodec/opt.h>
}

#include <dige/recorder.h>
#include <dige/window.h>

namespace dg
{
  std::map<const std::string, boost::shared_ptr<recorder> > recorder::recorders_;
  bool recorder::ffmpeg_initialized_ = false;


  recorder::recorder(const std::string& path)
    : avcodec_(0),
      avcontext_(0),
      swcontext_(0),
      yuvframe_(0),
      rgbframe_(0),
      video_buffer_size_(0),
      output_(path.c_str(), std::ios::binary),
      init_failed_(false),
      window_capture_(0),
      window_capture_size_(0)
  {
    if (!ffmpeg_initialized_)
    {
      avcodec_init();
      avcodec_register_all();
      ffmpeg_initialized_ = true;
    }

    if (output_.bad())
      std::cerr << "Cannot open " << path << " for writting." << std::endl;
  }

  recorder::~recorder()
  {
    if (!init_failed_)
    {
      // record delayed frames.
      unsigned frame_size = 1;
      while (frame_size)
      {
        frame_size = avcodec_encode_video(avcontext_, video_buffer_, video_buffer_size_, NULL);
        output_.write((char*)video_buffer_, frame_size);
      }

      // add mpeg sequence at the end
      video_buffer_[0] = 0x00;
      video_buffer_[1] = 0x00;
      video_buffer_[2] = 0x01;
      video_buffer_[3] = 0xb7;
      output_.write((char*)video_buffer_, 4);
      output_.close();

      avcodec_close(avcontext_);

      av_free(avcontext_);
      sws_freeContext(swcontext_);
      av_free(yuvframe_);
      av_free(rgbframe_);
      delete [] video_buffer_;
      delete [] window_capture_;
    }
  }

  void recorder::init_context(unsigned width, unsigned height)
  {
    assert(!avcontext_);

    if (output_.bad())
    {
      goto init_failed;
    }

    // find the mpeg1 video encoder
    avcodec_ = avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);
    if (!avcodec_)
    {
      std::cerr << "Codec not found" << std::endl;
      goto init_failed;
    }

    avcontext_ = avcodec_alloc_context();

    yuvframe_ = avcodec_alloc_frame();
    rgbframe_ = avcodec_alloc_frame();

    // put sample parameters
    avcontext_->bit_rate = 400000;
    // resolution must be a multiple of two
    avcontext_->width = width;
    avcontext_->height = height;
    // frames per second
    avcontext_->time_base= (AVRational){1,25};
    avcontext_->gop_size = 10; // emit one intra frame every ten frames
    avcontext_->max_b_frames=1;
    avcontext_->pix_fmt = PIX_FMT_YUV420P;
    //av_set_int(avcontext_, "dia", 4);

    // open the codec.
    if (avcodec_open(avcontext_, avcodec_) < 0)
    {
      std::cerr << "Could not open codec" << std::endl;
      goto init_failed;
    }

    // alloc image and output buffer
    video_buffer_size_ = 100000;
    video_buffer_ = new uint8_t[video_buffer_size_];

    // Initialization of ffmpeg frames.
    {
      unsigned size = avcontext_->width * avcontext_->height;
      window_capture_size_ = size * 3 * sizeof(char); // size for RGB
      window_capture_ = new char[window_capture_size_];
      window_capture_width_ = avcontext_->width;
      window_capture_height_ = avcontext_->height;

      rgbframe_->data[0] = (uint8_t*) window_capture_;
      rgbframe_->linesize[0] = avcontext_->width * 3 * sizeof(char);

      yuvframe_->data[0] = new uint8_t[(size * 3) / 2];
      yuvframe_->data[1] = yuvframe_->data[0] + size;
      yuvframe_->data[2] = yuvframe_->data[1] + size / 4;
      yuvframe_->linesize[0] = avcontext_->width;
      yuvframe_->linesize[1] = avcontext_->width / 2;
      yuvframe_->linesize[2] = avcontext_->width / 2;
    }

    // Swscale context.
    swcontext_ = sws_getContext(width, height, PIX_FMT_RGB24,
                                     width, height, PIX_FMT_YUV420P,
                                     SWS_FAST_BILINEAR,
                                     0, 0, 0);
    if(!swcontext_)
    {
      std::cerr<< "Cannot initialize the swscale conversion context" << std::endl;
      goto init_failed;
    }

    return;

  init_failed:
    init_failed_ = true;
    if (avcontext_) av_free(avcontext_);
    if (swcontext_) sws_freeContext(swcontext_);
    if (yuvframe_) av_free(yuvframe_);
    if (rgbframe_) av_free(rgbframe_);
    if (video_buffer_) delete [] video_buffer_;
    if (window_capture_) delete [] window_capture_;
    output_.close();
    std::cerr << "Video recording disabled." << std::endl;
    return;
  }

  void
  recorder::operator<<=(window& w)
  {
    if (!avcontext_ && !init_failed_)
      init_context(w.width(), w.height());
    if (init_failed_)
      return;

    unsigned old_width = window_capture_width_;
    unsigned old_height = window_capture_height_;
    w.dump_rgb_frame_buffer(window_capture_, window_capture_size_, window_capture_width_, window_capture_height_);
    if (old_width != window_capture_width_ || old_height != window_capture_height_)
    {
      std::cout << "new context" << std::endl;

      sws_freeContext(swcontext_);
      swcontext_ = sws_getContext(window_capture_width_, window_capture_height_, PIX_FMT_RGB24,
                                  avcontext_->width, avcontext_->height, PIX_FMT_YUV420P,
                                  SWS_FAST_BILINEAR,
                                  0, 0, 0);
      rgbframe_->data[0] = (uint8_t*) window_capture_;
      rgbframe_->linesize[0] = window_capture_width_ * 3 * sizeof(char);
    }


    // Flip and convert the image to YUV for video encoding.
    uint8_t* data = rgbframe_->data[0] +
      window_capture_width_ * 3 * (window_capture_height_ - 1);

    unsigned s = -window_capture_width_ * 3;
    uint8_t* tmp[1] = { data };
    int stride[1] = { s };
    int r = sws_scale(swcontext_, tmp, stride, 0,
                      window_capture_height_, yuvframe_->data, yuvframe_->linesize);

    // Encode video.
    unsigned encode_size
      = avcodec_encode_video(avcontext_, video_buffer_, video_buffer_size_,
                             yuvframe_);
    output_.write((char*)video_buffer_, encode_size);
  }

  std::map<const std::string, boost::shared_ptr<recorder> >&
  recorder::recorders()
  {
    return recorders_;
  }

  recorder& record(const std::string& path)
  {
    std::map<const std::string, boost::shared_ptr<recorder> >::const_iterator it
      = recorder::recorders().find(path);
    if (it != recorder::recorders().end())
    {
      return *((*it).second.get());
    }
    else
    {
      recorder* r = new recorder(path);
      recorder::recorders()[path] = boost::shared_ptr<recorder>(r);
      return *r;
    }
  }

} // end of namespace dg.
