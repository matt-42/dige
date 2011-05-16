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
**\file   event_set.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Feb 27 23:07:40 2011
**
**\brief  event_set header.
**
**
*/

#ifndef DIGE_EVENT_SET_H_
# define DIGE_EVENT_SET_H_

# include <boost/shared_ptr.hpp>
# include <dige/event/event.h>

namespace dg
{

  namespace event
  {
    template <typename T>
    class event_set
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

    class abstract_event_set;
    template <typename T>
    class generic_event_set;

    /*!
    ** abstract event_set class
    */
    class abstract_event_set
    {
    public:
      virtual bool matches(const any_event& e) const = 0;
    };

    /*!
    ** generic_event_set class.
    */
    template <typename T>
    class generic_event_set : public abstract_event_set
    {
    public:
      generic_event_set(const T& e)
        : e_(e)
      {
      }

      bool matches(const any_event& b) const
      {
        return e_.matches(b);
      }

      const T& event_set() const
      {
        return e_;
      }

    private:
      T e_;
    };


    class any_event_set
    {
    public:
      any_event_set();

      any_event_set(const any_event_set& e);
      any_event_set(const any_event& e);

      template <typename T>
      any_event_set(const event_set<T>& e)
        : event_set_(new generic_event_set<T>(e.subcast()))
      {
      }

      template <typename T>
      any_event_set& operator=(const T& e)
      {
        event_set_ = new T(e);
        return *this;
      }

      any_event_set& operator=(const any_event_set& e);

      const abstract_event_set* event_set() const;

    private:
      boost::shared_ptr<abstract_event_set> event_set_;
    };

    bool event_match(const any_event_set& s, const any_event& e);
    bool event_match(const any_event& e, const any_event_set& s);

    template <typename T>
    bool event_match(const event_set<T>& a, const any_event& b)
    {
      return a.subcast().matches(b);
    }

    template <typename T>
    bool event_match(const any_event& a, const event_set<T>& b)
    {
      return b.subcast().matches(a);
    }

  } // end of namespace event.

} // end of namespace dg.


#endif
