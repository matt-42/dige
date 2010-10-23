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
/*!
**\file   internal_texture.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Oct 23 19:31:37 2010
**
**\brief  internal_texture implemetation.
**
**
*/

namespace dg
{

  template <typename T>
  internal_texture<T>::internal_texture(const T& tex)
    : texture_(tex)
  {
  }

  template <typename T>
  internal_texture<T>::internal_texture(const internal_texture& t)
    : texture_(t.texture_)
  {
  }

  template <typename T>
  internal_texture<T>&
  internal_texture<T>::operator=(const internal_texture& t)
  {
    texture_ = t.texture_;
    return *this;
  }

  template <typename T>
  internal_texture<T>::~internal_texture()
  {
  }


  template <typename T>
  void internal_texture<T>::load()
  {
    return texture_.load();
  }

  template <typename T>
  void internal_texture<T>::unload()
  {
    return texture_.unload();
  }

  template <typename T>
  unsigned
  internal_texture<T>::width() const
  {
    return texture_.width();
  }

  template <typename T>
  unsigned
  internal_texture<T>::height() const
  {
    return texture_.height();
  }

  template <typename T>
  GLuint internal_texture<T>::gl_id() const
  {
    return texture_.gl_id();
  }


} // end of namespace dg.
