// Copyright (C) 2010, 2011 Matthieu Garrigues
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

#ifndef DIGE_TEXTURE_HPP_
# define DIGE_TEXTURE_HPP_

# include <cassert>
# include <dige/error.h>

namespace dg
{
  texture::texture()
    : width_(0),
      height_(0),
      comp_type_(0),
      format_(0),
      filter_(0),
      buffer_(0),
      gl_id_(0)
  {
  }

  texture::texture(unsigned width, unsigned height,
                   GLuint comp_type, GLuint format,
                   GLuint filter,
                   const char* buffer)
    : width_(width),
      height_(height),
      comp_type_(comp_type),
      format_(format),
      filter_(filter),
      buffer_(buffer),
      gl_id_(0)
  {
  }

  texture::texture(const texture& t)
    : width_(t.width_),
      height_(t.height_),
      comp_type_(t.comp_type_),
      format_(t.format_),
      filter_(t.filter_),
      buffer_(t.buffer_),
      gl_id_(t.gl_id_)
  {
  }

  texture& texture::operator=(const texture& t)
  {
    width_ = t.width_;
    height_ = t.height_;
    comp_type_ = t.comp_type_;
    format_ = t.format_;
    filter_ = t.filter_;
    buffer_ = t.buffer_;
    gl_id_ = t.gl_id_;
    return *this;
  }

  texture::~texture()
  {
  }


  void texture::load()
  {
    assert(buffer_);
    glGenTextures(1, &gl_id_);
    check_gl_error();
    assert(gl_id_);
    glBindTexture(GL_TEXTURE_2D, gl_id_);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D,
                 0, GL_RGB, width_, height_,
                 0, format_, comp_type_, buffer_);
    check_gl_error();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void texture::unload()
  {
    if (gl_id_)
    {
      glDeleteTextures(1, &gl_id_);
      gl_id_ = 0;
    }
  }

  unsigned
  texture::width() const
  {
    return width_;
  }

  unsigned
  texture::height() const
  {
    return height_;
  }

  GLuint texture::gl_id() const
  {
    assert(gl_id_);
    return gl_id_;
  }


} // end of namespace dg.

#endif
