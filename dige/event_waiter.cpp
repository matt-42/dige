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
**\file   event_waiter.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 25 09:54:58 2010
**
**\brief  event_waiter implementation.
**
**
*/

#include <QObject>
#include <QApplication>
#include <QMouseEvent>

#include <dige/displaylist.h>
#include <dige/singleton.h>
#include <dige/gl_widget.h>
#include <dige/event_waiter.h>

namespace dg
{
  event_waiter::event_waiter()
    : b_(false)
  {
  }

  bool event_waiter::eventFilter(QObject *obj, QEvent *event)
  {
    gl_widget* w = (gl_widget*)(obj);

    if (event->type() == to_wait_)
    {
      b_ = true;
      expected_ = 0;
    }
    return false;
  }

  void
  event_waiter::start_waiting_for(QEvent::Type e)
  {
    to_wait_ = e;
    b_ = false;
    expected_ = 0;
  }

  bool
  event_waiter::event_arrived()
  {
    return b_;
  }

  QEvent*
  event_waiter::expected()
  {
    return expected_;
  }

} // end of namespace dg.
