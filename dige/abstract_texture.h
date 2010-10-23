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
**\file   abstract_texture.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Oct 23 18:57:17 2010
**
**\brief  abstract_texture header.
**
**
*/

#ifndef DIGE_ABSTRACT_TEXTURE_H_
# define DIGE_ABSTRACT_TEXTURE_H_

# ifdef WIN32
#  include <windows.h>
# endif

# include <GL/gl.h>

namespace dg
{

  class abstract_texture
  {
  public:
    /*!
    ** Default constructor.
    ** Create an empty abstract_texture.
    */
    abstract_texture();

    /*!
    ** Destructor.
    ** Delete the abstract_texture from the video memory if image has been transfered.
    **
    */
    virtual ~abstract_texture();

    /// \return width of the abstract_texture.
    virtual unsigned width() const = 0;
    /// \return height of the abstract_texture.
    virtual unsigned height() const = 0;

    /// Load the abstract_texture on the video memory.
    virtual void load() = 0;
    /// Delete the abstract_texture from the video memory.
    virtual void unload() = 0;

    /// \return The OpenGL texture id.
    virtual GLuint gl_id() const = 0;

  };

} // end of namespace dg.

#endif
