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
**\file   point2d.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Sep  7 23:34:02 2010
**
**\brief  point2d header.
**
**
*/

#ifndef DIGE_POINT2D_H_
# define DIGE_POINT2D_H_

# include <iostream>

namespace dg
{

  /*!
  ** Simple and generic 2d point.
  **
  */
  template <typename T>
  class point2d
  {
  public:
    /// Default constructor.
    /// No initialization.
    point2d() {}

    /*!
    ** Constructor from coordinates.
    **
    ** \param x x coordinate.
    ** \param y y coordinate.
    */
    point2d(T x, T y)
    {
      data_[0] = x;
      data_[1] = y;
    }

    /*!
    ** Copy constructor.
    **
    ** \param p a point
    */
    point2d(const point2d<T>& p)
    {
      data_[0] = p[0];
      data_[1] = p[1];
    }

    /*!
    ** Assigment.
    **
    ** \param p a point
    **
    ** \return *this
    */
    point2d<T>& operator=(const point2d<T>& p)
    {
      data_[0] = p[0];
      data_[1] = p[1];
      return *this;
    }

    /*!
    ** Accessor.
    **
    ** \param i position of coordinate (must be either 0 or 1).
    **
    ** \return the coordinate.
    */
    T& operator[](unsigned i)
    {
      return data_[i];
    }

    /*!
    ** Const accessor.
    **
    ** \param i position of coordinate (must be either 0 or 1).
    **
    ** \return the coordinate.
    */
    const T& operator[](unsigned i) const
    {
      return data_[i];
    }

  private:
    T data_[2];                 /*!< Coordinates. */
  };

  /*!
  ** Print operator.
  **
  ** \param os output stream
  ** \param p a point
  **
  ** \return the output stream
  */
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const point2d<T>& p)
  {
    return os << "P(" << p[0] << ", " << p[1] << ")";
  }

} // end of namespace dg.

#endif
