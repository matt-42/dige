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

namespace dg
{

  /*!
  ** Event_Waiter.
  */
  class event_waiter : public QObject, public singleton<event_waiter>
  {
  private:
    /// Constructor.
    event_waiter();

  public:
    friend class singleton<event_waiter>;

    /*!
    ** Filter events.
    **
    ** \param obj watched object.
    ** \param e event
    **
    ** \return true if the event has been catched.
    */
    bool eventFilter(QObject *obj, QEvent *event);

    void start_waiting_for(QEvent::Type e);

    bool event_arrived();

    QEvent* expected();

  private:
    QEvent::Type to_wait_;
    bool b_;
    QEvent* expected_;
  };

} // end of namespace dg.

#endif
