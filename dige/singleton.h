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
**\file   singleton.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  singleton header.
**
**
*/

#ifndef DIGE_SINGLETON_H_
# define DIGE_SINGLETON_H_

namespace dg
{

  /*!
  ** Classic generic singleton.
  */
  template <typename T>
  class singleton
  {
  protected:
    /*!
    ** Default constructor.
    */
    inline singleton() {}

  public:
    /*!
    ** Instance accessor.
    **
    ** \return the singleton instance.
    */
    static inline T& instance()
    {
      if (!instance_)
        instance_ = new T();
      return *instance_;
    }

  private:
    static T* instance_;
  };

  template <typename T>
  T* singleton<T>::instance_ = 0;

} // end of namespace dg.

#endif
