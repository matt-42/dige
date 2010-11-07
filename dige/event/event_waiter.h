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
**\file   event_waiter.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  event_waiter header.
**
**
*/

#ifndef DIGE_EVENT_WAITER_H_
# define DIGE_EVENT_WAITER_H_

# include <QObject>

# include <dige/singleton.h>
# include <dige/event/event.h>

class QEvent;

namespace dg
{

  /*!
  ** Event_Waiter.
  */
  template <typename U>
  class event_waiter : public QObject, public singleton<event_waiter<U> >
  {
  private:
    /// Constructor.
    event_waiter();

  public:
    friend class singleton<event_waiter<U> >;

    /*!
    ** Filter events.
    **
    ** \param obj watched object.
    ** \param e event
    **
    ** \return true if the event has been catched.
    */
    bool eventFilter(QObject *obj, QEvent *event);

    void start_waiting_for(const U& e);

    bool event_match();

    any_event event();

  private:
    U to_wait_;
    bool b_;
    any_event event_;
  };

} // end of namespace dg.

# include <dige/event/event_waiter.hpp>

#endif

