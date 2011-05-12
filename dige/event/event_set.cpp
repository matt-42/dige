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
**\file   event_set.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Feb 27 23:04:12 2011
**
**\brief  event_set implementation.
**
**
*/

# include <dige/event/event_set.h>
# include <dige/event/or_event.h>

namespace dg
{

  namespace event
  {

    any_event_set::any_event_set()
    {
    }

    any_event_set::any_event_set(const any_event_set& e)
      : event_set_(e.event_set_)
    {
    }

    any_event_set::any_event_set(const any_event& e)
      : event_set_(new generic_event_set<or_event>(or_event() | e))
    {
    }

    any_event_set& any_event_set::operator=(const any_event_set& e)
    {
      event_set_ = e.event_set_;
      return *this;
    }

    const abstract_event_set* any_event_set::event_set() const
    {
      return event_set_.get();
    }

    bool event_match(const any_event_set& s, const any_event& e)
    {
      if (s.event_set() && e.event())
        return s.event_set()->matches(e);
      else
        return false;
    }

    bool event_match(const any_event& e, const any_event_set& s)
    {
      return event_match(s, e);
    }

  } // end of namespace event.

} // end of namespace dg.
