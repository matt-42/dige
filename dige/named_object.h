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
**\file   named_object.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Dec  4 10:47:25 2010
**
**\brief  Named object header
**
**
*/

#ifndef DIGE_NAMED_OBJECT_H_
# define DIGE_NAMED_OBJECT_H_

# include <map>
# include <string>

namespace dg
{

  template <typename T>
  class named_object
  {
  public:

    /// Associate all the created instances with theis names.
    static const std::map<const std::string, T*>& instances()
    {
      return instances_;
    }

  private:

    static std::map<const std::string, T*> instances_; /*!< List all the created instances. */

    template <typename U>
    friend U& named_instance(const std::string& name);

    template <typename U, typename A1>
    friend U& named_instance(const std::string& name, A1& a1);
    template <typename U, typename A1, typename A2>
    friend U& named_instance(const std::string& name, A1& a1, A2& a2);
    template <typename U, typename A1, typename A2, typename A3>
    friend U& named_instance(const std::string& name, A1& a1, A2& a2, A3& a3);
  };

  template <typename T>
  std::map<const std::string, T*> named_object<T>::instances_;

  template <typename T>
  T& named_instance(const std::string& name)
  {
    typename std::map<const std::string, T*>::const_iterator it
      = named_object<T>::instances_.find(name);
    if (it != named_object<T>::instancess_.end())
      return *((*it).second);
    else
    {
      T* e = new T(name);
      named_object<T>::instances_[name] = e;
      return *e;
    }
  }

  template <typename T, typename A1>
  T& named_instance(const std::string& name,
                      A1& a1)
  {
    typename std::map<const std::string, T*>::const_iterator it
      = named_object<T>::instances_.find(name);
    if (it != named_object<T>::instances_.end())
      return *((*it).second);
    else
    {
      T* e = new T(name, a1);
      named_object<T>::instances_[name] = e;
      return *e;
    }
  }

  template <typename T, typename A1, typename A2>
  T& named_instance(const std::string& name,
                    A1& a1,
                    A2& a2)
  {
    typename std::map<const std::string, T*>::const_iterator it
      = named_object<T>::instances_.find(name);
    if (it != named_object<T>::instances_.end())
      return *((*it).second);
    else
    {
      T* e = new T(name, a1, a2);
      named_object<T>::instances_[name] = e;
      return *e;
    }
  }

  template <typename T, typename A1, typename A2, typename A3>
  T& named_instance(const std::string& name,
                    A1& a1,
                    A2& a2,
                    A3& a3)
  {
    typename std::map<const std::string, T*>::const_iterator it
      = named_object<T>::instances_.find(name);
    if (it != named_object<T>::instances_.end())
      return *((*it).second);
    else
    {
      T* e = new T(name, a1, a2, a3);
      named_object<T>::instances_[name] = e;
      return *e;
    }
  }

} // end of namespace dige.

#endif
