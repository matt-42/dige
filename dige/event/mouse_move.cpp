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
**\file   mouse_move.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 14:23:15 2010
**
**\brief  mouse_move implementation.
**
**
*/

# include <iostream>
# include <QObject>
# include <QEvent>
# include <QMouseEvent>
# include <dige/event/mouse_move.h>

namespace dg
{

  namespace event
  {

    mouse_move::mouse_move()
      : widget_(0)
    {
    }

    mouse_move::mouse_move(QObject* widget, float x, float y)
      : widget_(widget)
    {
      pos_[0] = x;
      pos_[1] = y;
    }

    bool mouse_move::operator==(const mouse_move& b) const
    {
      if (!widget_ || !b.widget_)
        return true;
      else
        return b.widget_ == widget_;
    }

    const float* mouse_move::pos() const
    {
      return pos_;
    }

    any_event make_mouse_move(QObject *obj, QEvent *event)
    {
      if (event->type() == QEvent::MouseMove)
      {
	const QMouseEvent& e = * static_cast<QMouseEvent*>(event);
        return mouse_move(obj, e.pos().x(), e.pos().y());
      }

      return any_event();
    }

  } // end of namespace event.

} // end of namespace dg.
