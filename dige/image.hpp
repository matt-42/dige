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

#ifndef IMAGE_HPP_
# define IMAGE_HPP_

# include <dige/value_traits.h>

namespace dg
{

  template <typename F, typename C>
  image<F, C>::image()
    : width_(0),
      height_(0),
      buffer_(0)
  {
  }

  template <typename F, typename C>
  image<F, C>::image(unsigned width, unsigned height,
                        const char* buffer)
    : width_(width),
      height_(height),
      buffer_(buffer)
  {
  }

  template <typename F, typename C>
  image<F, C>::image(const image& t)
    : width_(t.width_),
      height_(t.height_),
      buffer_(t.buffer_)
  {
  }

  template <typename F, typename C>
  image<F, C>& image<F, C>::operator=(const image& t)
  {
    width_ = t.width_;
    height_ = t.height_;
    buffer_ = t.buffer_;
    return *this;
  }

  template <typename F, typename C>
  unsigned
  image<F, C>::width() const
  {
    return width_;
  }

  template <typename F, typename C>
  unsigned
  image<F, C>::height() const
  {
    return height_;
  }

  template <typename F, typename C>
  const typename image<F, C>::value_type*
  image<F, C>::buffer() const
  {
    return buffer_;
  }


  template <typename F, typename C>
  texture adapt(const image<F, C>& i)
  {
    return texture(i.width(), i.height(),
                   trait::gl_component_type<C>::ret,
                   F::to_gl_format, GL_NEAREST,
                   i.buffer());
  }

} // end of namespace dg.

#endif
