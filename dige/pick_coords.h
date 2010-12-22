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
**\file   pick_coords.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  pick_coords header.
**
**
*/

#ifndef DIGE_PICK_COORDS_H_
# define DIGE_PICK_COORDS_H_

# include <dige/point2d.h>
# include <dige/widgets/image_view.h>

namespace dg
{

  template <typename C>
  void pick_coords(const std::string& window, C& x, C& y)
  {
    point2d<int> p = display(window).selected_coords();
    x = p[0];
    y = p[1];
  }

  void wait_for_dblclick();

  template <typename C>
  void pick_coords_pause(const std::string& window, C& x, C& y)
  {
    wait_for_dblclick();
    pick_coords(window, x, y);
  }

} // end of namespace dg.

#endif

