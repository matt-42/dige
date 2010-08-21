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

#ifndef DIGE_RECORDER_H_
# define DIGE_RECORDER_H_

# include <map>
# include <fstream>
# include <memory>
# include <boost/shared_ptr.hpp>

extern "C"
{
# include <libavcodec/avcodec.h>
# include <libswscale/swscale.h>
# include <libavcodec/opt.h>
}
# include <dige/window.h>

namespace dg
{

  class recorder
  {
  public:
    inline recorder(const std::string& title);
    inline ~recorder();

    inline void operator<<=(window& w);

    static inline std::map<const std::string, boost::shared_ptr<recorder> >& recorders();

  private:
    inline void add_frame();
    inline void init_context(unsigned width, unsigned height);

    static std::map<const std::string, boost::shared_ptr<recorder> > recorders_;
    static bool ffmpeg_initialized_;

    AVCodec* avcodec_;
    AVCodecContext* avcontext_;
    SwsContext* swcontext_;
    AVFrame* yuvframe_;
    AVFrame* rgbframe_;
    uint8_t* video_buffer_;
    int video_buffer_size_;
    std::ofstream output_;
    bool init_failed_;
    char* window_capture_;
    unsigned window_capture_size_;
    unsigned window_capture_width_;
    unsigned window_capture_height_;
  };

  inline recorder& record(const std::string& path);

} // end of namespace dg.

# include <dige/recorder.hpp>

#endif
