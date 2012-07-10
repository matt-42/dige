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
#include <boost/cstdint.hpp>

using boost::uint8_t;
using boost::uint16_t;
using boost::uint32_t;
using boost::uint64_t;
using boost::int8_t;
using boost::int16_t;
using boost::int32_t;
using boost::int64_t;

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavcodec/opt.h>
#include <libavutil/error.h>
}

#include <dige/recorder.h>
#include <dige/widgets/image_view.h>



namespace dg
{
  std::map<const std::string, boost::shared_ptr<recorder> > recorder::recorders_;
  bool recorder::ffmpeg_initialized_ = false;

//#define VIDEO_CODEC CODEC_ID_MPEG2VIDEO
#define VIDEO_CODEC CODEC_ID_MPEG4
  //#define VIDEO_CODEC CODEC_ID_H264
//#define VIDEO_CODEC CODEC_ID_FFVHUFF

#define FRAME_FORMAT PIX_FMT_YUV420P

  recorder::recorder(const std::string& path)
    : avcodec_(0),
      avcontext_(0),
      swcontext_(0),
      yuvframe_(0),
      rgbframe_(0),
      video_buffer_(0),
      video_buffer_size_(0),
      output_(path.c_str(), std::ios::binary),
      path_(path),
      init_failed_(false),
      window_capture_(0),
      window_capture_size_(0)
  {
    if (!ffmpeg_initialized_)
    {
      //avcodec_init();
      avcodec_register_all();
      av_register_all();
      av_log_set_level(10);
      ffmpeg_initialized_ = true;
    }

    if (output_.bad())
      std::cerr << "Cannot open " << path << " for writting." << std::endl;
  }

  recorder::~recorder()
  {
    if (!init_failed_ && avcontext_)
    {
      // record delayed frames.
      unsigned frame_size = 1;
      while (frame_size)
      {
        frame_size = avcodec_encode_video(avcontext_, video_buffer_, video_buffer_size_, NULL);
        if (frame_size > 0)
        {
          AVPacket pkt;
          av_init_packet(&pkt);
          assert(avcontext_ && avcontext_->coded_frame);
          if(avcontext_->coded_frame->key_frame)
            pkt.flags |= AV_PKT_FLAG_KEY;
          pkt.stream_index = video_st_->index;
          pkt.data = video_buffer_;
          pkt.size = frame_size;

          int ret = av_write_frame(fmtcontext_, &pkt);
          assert(ret >= 0);
        }
      }

      av_write_trailer (fmtcontext_);
      avio_close (fmtcontext_->pb);

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

    outputfmt_ = av_guess_format ("avi", NULL, NULL);
    assert(outputfmt_);
    fmtcontext_ = avformat_alloc_context();
    fmtcontext_->oformat = outputfmt_;

    std::copy(path_.begin(), path_.end(), fmtcontext_->filename);

    assert(outputfmt_->video_codec != CODEC_ID_NONE);

    video_st_ = av_new_stream(fmtcontext_, 0);
    assert(video_st_);


    avcontext_ = video_st_->codec;
    avcodec_get_context_defaults(avcontext_);

    yuvframe_ = avcodec_alloc_frame();
    rgbframe_ = avcodec_alloc_frame();

    avcontext_->codec_id = VIDEO_CODEC;
    avcontext_->codec_type = AVMEDIA_TYPE_VIDEO;

    avcontext_->width = width;
    avcontext_->height = height;
    avcontext_->flags = CODEC_FLAG_4MV | CODEC_FLAG_AC_PRED | CODEC_FLAG_PASS1;
    avcontext_->mb_decision = FF_MB_DECISION_RD;
    avcontext_->me_cmp = 2;
    avcontext_->me_sub_cmp = 2;
    avcontext_->trellis = 2;

    avcontext_->bit_rate = 2000000*1000;
    avcontext_->bit_rate_tolerance = avcontext_->bit_rate;
    avcontext_->b_frame_strategy = 1;
    avcontext_->coder_type = 1;
    avcontext_->me_method = ME_EPZS;
    avcontext_->me_subpel_quality = 5;
    avcontext_->i_quant_factor = 0.71;
    avcontext_->qcompress = 0.6;
    avcontext_->max_qdiff = 4;
    //DEPRECATED avcontext_->directpred = 1;
    avcontext_->gop_size = 300;
    avcontext_->max_b_frames=3;

    avcontext_->time_base.den = 25;
    avcontext_->time_base.num = 1;

    avcontext_->pix_fmt = FRAME_FORMAT;

    av_dump_format(fmtcontext_, 0, path_.c_str(), 1);

    // find the mpeg1 video encoder
    avcodec_ = avcodec_find_encoder(avcontext_->codec_id);

    if (!avcodec_)
    {
      std::cerr << "Codec not found" << std::endl;
      goto init_failed;
    }

    // open the codec.
    int err;
    if ((err = avcodec_open(avcontext_, avcodec_)) < 0)
    {
      char err_message[1000];
      memset(err_message, 0, 1000);
      int err_err = av_strerror(-err, err_message, 1000);
      std::cerr << "Could not open codec: error " << err_err << ": "
                << err_message << std::endl;
      goto init_failed;
    }

    // alloc image and output buffer
    video_buffer_size_ = 3000000;
    video_buffer_ = new uint8_t[video_buffer_size_];

    // Initialization of ffmpeg frames.
    {
      unsigned size = avcontext_->width * avcontext_->height;
      window_capture_size_ = 2*size * 3 * sizeof(unsigned char); // size for RGB
      window_capture_ = new unsigned char[window_capture_size_];
      window_capture_width_ = avcontext_->width;
      window_capture_height_ = avcontext_->height;


      rgbframe_->data[0] = (uint8_t*) window_capture_;
      rgbframe_->linesize[0] = avcontext_->width * 3 * sizeof(unsigned char);

      yuvframe_->data[0] = new uint8_t[(size * 3) / 2];
      yuvframe_->data[1] = yuvframe_->data[0] + size;
      yuvframe_->data[2] = yuvframe_->data[1] + size / 4;
      yuvframe_->linesize[0] = avcontext_->width;
      yuvframe_->linesize[1] = avcontext_->width / 2;
      yuvframe_->linesize[2] = avcontext_->width / 2;
    }

    // Swscale context.
    swcontext_ = sws_getCachedContext(0,
                                      width, height, PIX_FMT_RGB24,
                                      width, height, FRAME_FORMAT,
                                      SWS_POINT,
                                      0,
                                      0,
                                      0);
    if(!swcontext_)
    {
      std::cerr<< "Cannot initialize the swscale conversion context" << std::endl;
      goto init_failed;
    }

    /* open the output file, if needed */
    if (!(outputfmt_->flags & AVFMT_NOFILE))
    {
#ifdef URL_WRONLY
      if (avio_open (&fmtcontext_->pb, path_.c_str(), URL_WRONLY) < 0)
#else
      if (avio_open (&fmtcontext_->pb, path_.c_str(), AVIO_FLAG_WRITE) < 0)
#endif
      {
        std::cerr << "Could not open "<< path_ << std::endl;
        assert(0 && "Could not open ouput file");
      }
    }

    /* write the stream header, if any */
    avformat_write_header(fmtcontext_, NULL);

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
  recorder::operator<<=(widgets::image_view& w)
  {
  
    if (!avcontext_ && !init_failed_)
      init_context(w.width(), w.height());
    if (init_failed_)
      return;

    w.set_unresizable();
    unsigned old_width = window_capture_width_;
    unsigned old_height = window_capture_height_;
    w.dump_rgb_frame_buffer(window_capture_, window_capture_size_, window_capture_width_, window_capture_height_);

    if (old_width != window_capture_width_ || old_height != window_capture_height_)
    {
      std::cout << "new context" << std::endl;

      sws_getCachedContext(swcontext_,
                           window_capture_width_, window_capture_height_,
                           PIX_FMT_RGB24,
                           avcontext_->width, avcontext_->height,
                           FRAME_FORMAT,
                           SWS_BILINEAR,
                           0, 0, 0);
      rgbframe_->data[0] = (uint8_t*) window_capture_;
      rgbframe_->linesize[0] = window_capture_width_ * 3 * sizeof(unsigned char);
    }


    // Flip and convert the image to YUV for video encoding.
    uint8_t* data = rgbframe_->data[0] +
      window_capture_width_ * 3 * (window_capture_height_ - 1);
    unsigned s = -window_capture_width_ * 3;

    uint8_t* tmp[1] = { data };
    int stride[1] = { s };
    // int r =
    sws_scale(swcontext_, tmp, stride, 0,
              window_capture_height_, yuvframe_->data, yuvframe_->linesize);

    // Encode video.
    int encode_size
      = avcodec_encode_video(avcontext_, video_buffer_, video_buffer_size_,
                             yuvframe_);

    if (encode_size > 0)
    {
      AVPacket pkt;
      av_init_packet(&pkt);

      if(avcontext_->coded_frame->key_frame)
        pkt.flags |= AV_PKT_FLAG_KEY;
      pkt.stream_index = video_st_->index;
      pkt.data = video_buffer_;
      pkt.size = encode_size;

      int ret = av_write_frame(fmtcontext_, &pkt);
      assert(ret >= 0);
    }
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
