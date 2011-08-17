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
**\file   image_view.hpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Aug 21 12:53:21 2010
**
**\brief  image_view header.
**
**
*/

#ifndef DIGE_IMAGE_VIEW_HPP_
# define DIGE_IMAGE_VIEW_HPP_

# include <dige/widgets/image_view.h>

namespace dg
{

  namespace widgets
  {

    template <typename T>
    image_view&
    image_view::operator<<(const T& i)
    {
      if (list_on_screen_)
      {
        unload_list();
        newline();
      }

      list_on_screen_ = false;
      dlist_ - i;
      return *this;
    }

  } // end of namespace widgets.

} // end of namespace dg.

#endif
