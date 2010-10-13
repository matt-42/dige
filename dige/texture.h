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
**\file   texture.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  texture header.
**
**
*/

#ifndef DIGE_TEXTURE_H_
# define DIGE_TEXTURE_H_

# ifdef WIN32
#  include <windows.h>
# endif

# include <GL/gl.h>

namespace dg
{

  /*!
  ** Encapsulate OpenGL textures managments. From an image hosted on
  ** the main memory, transfert data into a newly created OpenGL texture.
  **
  ** This type is well adapted to adapt non statically typed image
  ** since information about components and image format are not
  ** static in this class (unlike in the image class).
  **
  */
  class texture
  {
  public:
    /*!
    ** Default constructor.
    ** Create an empty texture.
    */
    inline texture();
    /*!
    ** Constructor from a "main memory" image.
    **
    ** \param width width
    ** \param height height

    ** \param comp_type OpenGL component type (GL_FLOAT, GL_INT).
    **                  "type" argument of glteximage2d.
    ** \param format OpenGL format (GL_RGB, GL_LUMINANCE, ...).
    ** \param filter Texture filter (GL_NEAREST, GL_LINEAR)
    ** \param buffer image data.
    */
    inline texture(unsigned width, unsigned height,
            GLuint comp_type, GLuint format,
            GLuint filter,
            const char* buffer);

    /*!
    ** Copy constructor
    **
    ** \param t a texture.
    */
    inline texture(const texture& t);

    /*!
    ** Assigment operator.
    **
    ** \param t a texture.
    */
    inline texture& operator=(const texture& t);

    /*!
    ** Destructor.
    ** Delete the texture from the video memory if image has been transfered.
    **
    */
    inline ~texture();

    /// \return width of the texture.
    inline unsigned width() const;
    /// \return height of the texture.
    inline unsigned height() const;

    /// Load the texture on the video memory.
    inline void load();
    /// Delete the texture from the video memory.
    inline void unload();

    /// \return The OpenGL texture id.
    inline GLuint gl_id() const;

  private:
    unsigned width_;            /*!< width. */
    unsigned height_;           /*!< height. */
    GLuint comp_type_;          /*!< OpenGL component type. */
    GLuint format_;             /*!< OpenGL format. */
    GLuint filter_;             /*!< OpenGL filter. */
    const char* buffer_;        /*!< image data. */
    GLuint gl_id_;              /*!< OpenGL texture id. */
  };

} // end of namespace dg.

# include <dige/texture.hpp>

#endif
