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
**\file   display.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Oct  3 15:51:07 2010
**
**\brief  display header.
**
**
*/

#ifndef DIGE_DISPLAY_H_
# define DIGE_DISPLAY_H_

# include <string>

namespace dg
{
  class window;

  /*!
  ** window factory. Retrieve the window named \p title. Create it if
  ** it doesn't exists.
  **
  ** \param width window width in pixel.
  ** \param height window height in pixel.
  **
  ** \return the window.
  */
  window& display(const std::string& title, unsigned width = 400,
                  unsigned height = 400);


  /*!
  ** Pause the current thread until the user press the space key in any of the
  ** window. It need at least one created window.
  */
  void pause();

} // end of namespace dg.

#endif
