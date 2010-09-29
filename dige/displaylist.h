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
**\file   displaylist.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Sep  7 23:34:02 2010
**
**\brief  displaylist header.
**
**
*/

#ifndef DIGE_DISPLAYLIST_H_
# define DIGE_DISPLAYLIST_H_

# include <iostream>

# include <vector>
# include <dige/texture.h>
# include <dige/rect2d.h>

namespace dg
{

  /// Layout.
  typedef std::vector<std::vector<rect2d> > layout;

  /*!
  ** List of drawables objects. Easy to build via operators - and +.
  **
  */
  class displaylist
  {
  public:
    /// Default constructor.
    displaylist();

    /*!
    ** Append an object to the current line.
    **
    ** \param i an object to be drawn.
    **
    ** \return *this.
    */
    template <typename T>
    displaylist& operator-(const T& i);

    /*!
    ** Append an object to a newly created line.
    **
    ** \param i an object to be drawn.
    **
    ** \return *this.
    */
    template <typename T>
    displaylist& operator+(const T& i);

    /// Load all objects on the video memory.
    void load();
    /// Unload all objects on the video memory.
    void unload();
    /*!
    ** Draw the list in the given dimensions.
    **
    ** \param width width,
    ** \param height height.
    */
    void draw(unsigned width, unsigned height);

    /*!
    ** Draw the list in the given dimensions and fill \p layout.
    **
    ** \param width width,
    ** \param height height.
    ** \param layout layout to fill with positions of images.
    */
    void draw(unsigned width, unsigned height, layout& layout);

    point2d<int> dlist_to_image_coord(const layout& l, const point2d<float>& p);

  private:
    /*!
    ** Draw the list in the given dimensions and fill \p layout if
    ** given.
    **
    ** \param width width,
    ** \param height height.
    ** \param layout layout to fill with positions of images.
    */
    void draw_(unsigned width, unsigned height, layout* layout = 0);

    /*!
    ** Recursivelly adapt the types until reaching a texture.
    **
    ** \param i an object.
    **
    ** \return \p i as a  texture.
    */
    template <typename T>
    texture adapt_rec(const T& i);

    /*!
    ** Recursivelly adapt the types until reaching a texture.
    ** Stop case.
    ** \param i an object.
    **
    ** \return \p i as a  texture.
    */
    texture adapt_rec(texture i);

    std::vector<std::vector<texture> > textures_; /*!< 2d array of textures. */
  };

  typedef displaylist dl;

} // end of namespace dg.

# include <dige/displaylist.hpp>

#endif
