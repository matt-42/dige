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

#include <QApplication>

#include <dige/displaylist.h>
#include <dige/need_qapp.h>
#include <dige/event/event.h>
#include <dige/event/event_waiter.h>
#include <dige/event/make_event.h>

namespace dg
{
  template <typename U>
  event_waiter<U>::event_waiter()
    : b_(false)
  {
  }

  template <typename U>
  bool
  event_waiter<U>::eventFilter(QObject *obj, QEvent *event)
  {
    any_event e = make_event(obj, event);

    if (dg::event_match(to_wait_, e))
    {
      b_ = true;
      event_ = e;
      QApplication::instance()->removeEventFilter(this);
      return false;
    }

    return false;
  }

  template <typename U>
  void
  event_waiter<U>::start_waiting_for(const any_event_set& e)
  {
    need_qapp();
    to_wait_ = e;
    b_ = false;
    QApplication::instance()->installEventFilter(this);
  }

  template <typename U>
  void
  event_waiter<U>::start_waiting_for(const any_event& e)
  {
    need_qapp();
    to_wait_ = any_event_set(e);
    b_ = false;
    QApplication::instance()->installEventFilter(this);
  }

  template <typename U>
  bool
  event_waiter<U>::event_match()
  {
    return b_;
  }

  template <typename U>
  any_event
  event_waiter<U>::event()
  {
    return event_;
  }

} // end of namespace dg.
