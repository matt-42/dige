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
**\file   internal_texture.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Oct 23 18:58:56 2010
**
**\brief  internal_texture header.
**
**
*/


#ifndef DIGE_INTERNAL_TEXTURE_H_
# define DIGE_INTERNAL_TEXTURE_H_

# ifdef WIN32
#  include <windows.h>
# endif

# include <GL/gl.h>

# include <dige/abstract_texture.h>

namespace dg
{

  template <typename T>
  class internal_texture : public abstract_texture
  {
  public:
    /*!
    ** Default constructor.
    ** Create an empty internal_texture.
    */
    internal_texture(const T& tex);

    /*!
    ** Copy constructor
    **
    ** \param t a internal_texture.
    */
    internal_texture(const internal_texture& t);

    /*!
    ** Assigment operator.
    **
    ** \param t a internal_texture.
    */
    internal_texture& operator=(const internal_texture& t);

    /*!
    ** Destructor.
    ** Delete the internal_texture from the video memory if image has been transfered.
    **
    */
    ~internal_texture();

    /// \return width of the internal_texture.
    unsigned width() const;
    /// \return height of the internal_texture.
    unsigned height() const;

    /// Load the internal_texture on the video memory.
    void load();
    /// Delete the internal_texture from the video memory.
    void unload();

    /// \return The OpenGL internal_texture id.
    GLuint gl_id() const;

  private:
    T texture_;
  };

} // end of namespace dg.

# include <dige/internal_texture.hpp>

#endif
