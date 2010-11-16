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
**\file   reset_panzoom.hpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 24 22:37:43 2010
**
**\brief  reset_panzoom header.
**
**
*/

# include <QObject>
# include <QEvent>

# include <dige/panzoom.h>
# include <dige/panzoom_control.h>
# include <dige/shortcuts/reset_panzoom.h>
# include <dige/gl_widget.h>

namespace dg
{
  /// Toggle fullscreen state of the active window.
  void reset_panzoom(QObject*, QEvent*)
  {
    gl_widget* w = panzoom::instance().focuswidget();
    if (!w)
      return;

    panzoom_control::instance().hide();

    w->scale() = 1;
    w->pan() = QPointF(0,0);
    w->updateGL();
  }

} // end of namespace dg.

