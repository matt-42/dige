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
**\file   event.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 15:09:38 2010
**
**\brief  event implementation
**
**
*/

# include <dige/event/event.h>

namespace dg
{

  any_event::any_event()
  {
  }

  any_event::any_event(const any_event& e)
    : event_(e.event_)
  {
  }

  any_event& any_event::operator=(const any_event& e)
  {
    event_ = e.event_;
    return *this;
  }

  const abstract_event* any_event::event() const
  {
    return event_.get();
  }

  bool operator==(const any_event& a, const any_event& b)
  {
    if (a.event() && b.event())
      return a.event()->operator==(*b.event());
    else
      return a.event() == b.event();
  }

  bool event_match(const any_event& a, const any_event& b)
  {
    return a == b;
  }


} // end of namespace dg.
