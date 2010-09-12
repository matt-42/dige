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
**\file   toggle_fullscreen.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  toggle_fullscreen header.
**
**
*/

#ifndef DIGE_TOGGLE_FULLSCREEN_H_
# define DIGE_TOGGLE_FULLSCREEN_H_

# include <QApplication>
# include <QWidget>

namespace dg
{
  /// Toggle fullscreen state of the active window.
  inline void toggle_fullscreen()
  {
    if (QApplication::activeWindow())
      if (QApplication::activeWindow()->isFullScreen())
        QApplication::activeWindow()->showNormal();
      else
        QApplication::activeWindow()->showFullScreen();
  }

} // end of namespace dg.

#endif

