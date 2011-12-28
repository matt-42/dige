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
**\file   dblclick.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 14:23:15 2010
**
**\brief  dblclick implementation.
**
**
*/

# include <iostream>
# include <QObject>
# include <QEvent>

# include <dige/event/dblclick.h>

namespace dg
{

  namespace event
  {

    dblclick::dblclick()
      : widget_(0)
    {
    }

    dblclick::dblclick(QObject* widget)
      : widget_(widget)
    {
    }

    bool dblclick::operator==(const dblclick& b) const
    {
      if (!widget_ || !b.widget_)
        return true;
      else
        return b.widget_ == widget_;
    }

    any_event make_dblclick(QObject *obj, QEvent *event)
    {
      if (event->type() == QEvent::MouseButtonDblClick)
        return dblclick(obj);

      return any_event();
    }

  } // end of namespace event.

} // end of namespace dg.
