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
**\file   wait_event.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 13:51:44 2010
**
**\brief  wait_event header.
**
**
*/

#ifndef DIGE_WAIT_EVENT_H_
# define DIGE_WAIT_EVENT_H_

# include <QObject>
# include <QApplication>
# include <QEvent>
# include <dige/window.h>
# include <dige/event/event_waiter.h>
# include <dige/event/or_event.h>
# include <dige/event/or_event.h>

namespace dg
{

  namespace event
  {

    template <typename U>
    any_event wait_event(const U& e)
    {
      event_waiter<U> w;
      w.start_waiting_for(e);
      while (!w.event_match())
      {
        QApplication::processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::AllEvents);
        QApplication::sendPostedEvents();
      }

      return w.event();
    }

#define for_each_event_until(E, C, U)           \
    for (dg::any_event E = dg::event::wait_event(C | U);     \
         !dg::event_match(U, E);                \
         E = dg::event::wait_event(C | U))

#define for_each_event(E, C)                    \
    for (dg::any_event E = dg::event::wait_event(C);         \
         ;                                      \
         E = dg::event::wait_event(C))

  } // end of namespace event.

} // end of namespace dg.

#endif
