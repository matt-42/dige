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
**\file   is_texture_type.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Oct 23 19:45:09 2010
**
**\brief  is_texture_type trait
**
**
*/

#ifndef DIGE_IS_TEXTURE_TYPE
# define DIGE_IS_TEXTURE_TYPE

# include <GL/glu.h>

namespace dg
{
  template <typename T>
  struct is_texture_type
  {
  private:
    template <typename U>
    static char   sfinae(typename U::dige_texture_type* x);

    template <typename U>
    static double sfinae(...);

  public:
    enum { val = sizeof(sfinae<T>(0)) == sizeof(char) };
    enum { not_val = !val };
  };
}

#endif
