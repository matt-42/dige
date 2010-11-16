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
**\file   event.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 11:31:52 2010
**
**\brief  Event header
**
**
*/

#ifndef DIGE_EVENT_H_
# define DIGE_EVENT_H_

# include <boost/shared_ptr.hpp>

namespace dg
{
  template <typename T>
  class Event
  {
  public:
    const T& subcast() const
    {
      return *(const T*)this;
    }

    T& subcast()
    {
      return *(T*)this;
    }
  };

  class abstract_event;
  template <typename T>
  class generic_event;

  /*!
  ** abstract event class
  */
  class abstract_event
  {
  public:
    virtual bool operator==(const abstract_event& b) const = 0;
    virtual const std::type_info& type() const = 0;
  };

  /*!
  ** generic_event class.
  */
  template <typename T>
  class generic_event : public abstract_event
  {
  public:
    generic_event(const T& e)
      : e_(e)
    {
    }

    bool operator==(const abstract_event& b) const
    {
      return type() == b.type() &&
      ((generic_event<T>*) &b)->e_ == e_;
    }

    const std::type_info& type() const
    {
      return typeid(T);
    }

    const T& event() const
    {
      return e_;
    }
  private:
    T e_;
  };


  class any_event
  {
  public:
    any_event();

    any_event(const any_event& e);

    template <typename T>
    any_event(const Event<T>& e)
      : event_(new generic_event<T>(e.subcast()))
    {
    }

    template <typename T>
    any_event& operator=(const T& e)
    {
      event_ = new T(e);
      return *this;
    }

    any_event& operator=(const any_event& e);

    const abstract_event* event() const;

  private:
    boost::shared_ptr<abstract_event> event_;
  };

  bool operator==(const any_event& a, const any_event& b);

  template <typename T>
  bool operator==(const any_event& a, const T& b)
  {
    return a.event() && a.event()->type() == typeid(T) &&
      *(generic_event<T>*)a.event() == b;
  }


  template <typename T>
  bool operator==(const Event<T>& e, const generic_event<T>& f)
  {
    return e.subcast() == f.event();
  }

  template <typename T>
  bool operator==(const generic_event<T>& e, const Event<T>& f)
  {
    return e.event() == f.subcast();
  }

  bool event_match(const any_event& a, const any_event& b);

  template <typename T>
  bool event_match(const Event<T>& a, const any_event& b)
  {
    return a == b;
  }

  template <typename T>
  bool event_match(const any_event& a, const Event<T>& b)
  {
    return a == b;
  }


} // end of namespace dg.

#endif
