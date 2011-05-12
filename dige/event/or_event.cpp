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
**\file   or_event.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Nov 16 21:46:01 2010
**
**\brief  or_event implementation
**
**
*/

#include <iostream>
#include <dige/event/or_event.h>

namespace dg
{

  namespace event
  {
    or_event::or_event()
    {
    }

    or_event::or_event(const or_event& o)
      : events_(o.events_)
    {
    }

    or_event&
    or_event::operator=(const or_event& o)
    {
      events_ = o.events_;
      return *this;
    }


    bool
    or_event::operator==(const or_event&) const
    {
      return false;
    }

    bool
    or_event::matches(const any_event& e) const
    {
      for (unsigned i = 0; i < events_.size(); i++)
      {
        if (events_[i] == e)
          return true;
      }
      return false;
    }

    or_event&
    or_event::operator|(const any_event& e)
    {
      events_.push_back(e);
      return *this;
    }

    bool event_match(const or_event& a, const any_event& b)
    {
      return a.matches(b);
    }

    bool event_match(const any_event& b, const or_event& a)
    {
      return a.matches(b);
    }

  } // end of namespace event.

} // end of namespace dg.
