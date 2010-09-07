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
**\file   image.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Sep  7 23:11:35 2010
**
**\brief  image header.
**
**
*/

#ifndef IMAGE_H_
# define IMAGE_H_

#include <dige/texture.hpp>

namespace dg
{

  /*!
  ** Represent an image hosted on the main memory. Should be used
  ** instead texture since it is more type-safe.
  **
  ** The format (rgb, gray level) and the components type are known at
  ** compile time.
  **
  */
  template <typename F, typename C>
  class image
  {
  public:
    /// Self type
    typedef image<F, C> self;

    /// Values type.
    typedef C value_type;

    /// Default constructor.
    image();

    /*!
    ** Constructor from an external image.
    **
    ** \param width width
    ** \param height height
    ** \param buffer image data
    */
    image(unsigned width, unsigned height,
          const value_type* buffer);

    /*!
    ** Copy constructor.
    **
    ** \param i an image.
    */
    image(const image& i);

    /*!
    ** Assignment.
    **
    ** \param i an image.
    **
    ** \return *this.
    */
    self& operator=(const image& i);

    /// \return width.
    unsigned width() const;
    /// \return height.
    unsigned height() const;
    /// \return image data.
    const value_type* buffer() const;

  private:
    unsigned width_;            /*!< width. */
    unsigned height_;           /*!< height. */
    const value_type* buffer_;  /*!< image data. */
  };

  /*!
  ** Translate an image into a texture.
  **
  ** \param i an image.
  **
  ** \return the corresponding texture.
  */
  template <typename F, typename C, unsigned S>
  texture adapt(const image<F, C>& i);

} // end of namespace dg.

# include <dige/image.hpp>

#endif
