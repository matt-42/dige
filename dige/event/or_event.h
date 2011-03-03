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
**\file   or_event.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 12:23:27 2010
**
**\brief  or_event header.
**
**
*/

#ifndef DIGE_OR_EVENT_H_
# define DIGE_OR_EVENT_H_

# include <vector>
# include <dige/event/event_set.h>

namespace dg
{

  class or_event : public Event_Set<or_event>
  {
  public:
    or_event();

    or_event(const or_event& o);

    or_event& operator=(const or_event& o);

    template  <typename T>
    or_event& operator|(const Event<T>& e)
    {
      events_.push_back(any_event(e.subcast()));
      return *this;
    }

    or_event& operator|(const any_event& e);

    bool matches(const any_event& e) const;
    bool operator==(const or_event& e) const;

  private:
    std::vector<any_event> events_;
  };

  template <typename T, typename U>
  or_event operator|(const Event<T>& e, const Event<U>& f)
  {
    return or_event() | e.subcast() | f.subcast();
  }

  template <typename U>
  or_event operator|(const any_event& e, const Event<U>& f)
  {
    return or_event() | e | f.subcast();
  }

  template <typename U>
  or_event operator|(const Event<U>& e, const any_event& f)
  {
    return or_event() | e.subcast() | f;
  }

  bool event_match(const or_event& a, const any_event& b);
  bool event_match(const any_event& b, const or_event& a);

} // end of namespace dg.

#endif
