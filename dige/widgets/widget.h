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
**\file   widget.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun May 29 21:45:06 2011
**
**\brief  Widget header.
**
**
*/

#ifndef DIGE_WIDGET_H_
# define DIGE_WIDGET_H_

namespace dg
{

  namespace widgets
  {

    /*!
    ** Widget concept.
    */
    template <typename T>
    class Widget
    {
    };

    /*!
    ** Downcast a Widget into its exact type.
    */
    template <typename T>
    T& exact(Widget<T>& x)
    {
      return *static_cast<T*>(&x);
    }

    /*!
    ** Downcast a Widget into its exact type.
    */
    template <typename T>
    const T& exact(const Widget<T>& x)
    {
      return *static_cast<const T*>(&x);
    }

  } // end of namespace widgets.

} // end of namespace dg.

#endif
