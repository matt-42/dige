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
**\file   rect2d.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Sep  7 23:34:02 2010
**
**\brief  rect2d header.
**
**
*/

#ifndef DIGE_RECT2D_H_
# define DIGE_RECT2D_H_

# include <iostream>

# include <dige/point2d.h>

namespace dg
{

  /*!
  ** Classic 2d rectangle using float coordinates.
  */
  class rect2d
  {
  public:
    /// Default constructor.
    inline rect2d() {}

    /*!
    ** Constructor from origin, width, height.
    **
    ** \param origin origin
    ** \param width width
    ** \param height height
    **
    */
    inline rect2d(const point2d<float>& origin, float width, float height)
      : origin_(origin),
      width_(width),
      height_(height)
    {
    }

    /*!
    ** Copy constructor.
    **
    ** \param r a rectangle.
    **
    */
    inline rect2d(const rect2d& r)
    {
      *this = r;
    }

    /*!
    ** Assigment.
    **
    ** \param r a rectangle.
    **
    ** \return *this.
    */
    inline rect2d& operator=(const rect2d& r)
    {
      origin_ = r.origin_;
      width_ = r.width_;
      height_ = r.height_;
      return *this;
    }

    /*!
    ** Inclusion test
    **
    ** \param p a point
    **
    ** \return true if the rectangle include \p p.
    */
    inline bool has(const point2d<float>& p) const
    {
      return p[0] >= origin_[0] && p[0] < (origin_[0] + width_) &&
        p[1] >= origin_[1] && p[1] < (origin_[1] + height_);
    }

    /*!
    ** Accessor.
    **
    ** \return the origin.
    */
    inline point2d<float> origin() const { return origin_; }

    /*!
    ** Accessor
    **
    ** \return the width.
    */
    inline float width() const           { return width_;  }

    /*!
    ** Accessor
    **
    ** \return the height.
    */
    inline float height() const          { return height_; }

  private:
    point2d<float> origin_;     /*!< origin. */
    float width_;               /*!< width.  */
    float height_;              /*!< height. */
  };

  /*!
  ** Print operator
  **
  ** \param os output stream.
  ** \param r a rectangle.
  **
  ** \return the output stream
  */
  inline std::ostream& operator<<(std::ostream& os, rect2d& r)
  {
    return os << "R(" << r.origin()
              << ", "  << r.origin()[0] + r.width()
              << "," << r.origin()[1] + r.height()
              << " " << r.width() << " * " << r.height() << ')';
  }


} // end of namespace dg.

#endif
