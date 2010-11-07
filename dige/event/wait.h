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
**\file   wait.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 13:51:44 2010
**
**\brief  wait header.
**
**
*/

#ifndef DIGE_WAIT_H_
# define DIGE_WAIT_H_

# include <QObject>
# include <QApplication>
# include <QEvent>
# include <dige/window.h>
# include <dige/event/event_waiter.h>
# include <dige/event/or_event.h>

namespace dg
{

  template <typename U>
  any_event wait(const U& e)
  {
    assert(window::windows().size() > 0);

    event_waiter<U>::instance().start_waiting_for(e);
    while (!event_waiter<U>::instance().event_match())
    {
      QApplication::processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::AllEvents);
      QApplication::sendPostedEvents();
    }

    return event_waiter<U>::instance().event();
  }

#define for_each_event(E, C, U)              \
  for (dg::any_event E = dg::wait(C | U);   \
       !dg::event_match(U, E);                              \
       E = dg::wait(C | U))

#define for_each_event_(C)                      \
  for (dg::any_event e = dg::wait(C);           \
       ;                                        \
       e = dg::wait(C))

} // end of namespace dg.

#endif
