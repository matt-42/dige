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
**\file   custom_events.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Feb 28 15:24:35 2011
**
**\brief  custom events declaration.
**
**
*/

#ifndef DIGE_CUSTOM_EVENTS_H_
# define DIGE_CUSTOM_EVENTS_H_

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

    enum custom_event
    {
      start = QEvent::User,
      slider_changed
    };

  } // end of namespace event.

} // end of namespace dg.

#endif
