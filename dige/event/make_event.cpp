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
**\file   make_event.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 14:15:17 2010
**
**\brief  make_event implementation.
**
**
*/

# include <dige/event/click_event.h>
# include <dige/event/key_release.h>

namespace dg
{

  typedef any_event (*event_factory)(QObject *obj, QEvent *event);

  event_factory factories[] =
  { make_click_event,
    make_key_release_event
  };

  any_event make_event(QObject *obj, QEvent *event)
  {
    any_event res;
    for (unsigned i = 0; i < sizeof(factories) / sizeof(event_factory); i++)
    {
      res = factories[i](obj, event);
      if (res.event())
        return res;
    }
    return res;
  }

} // end of namespace dg.
