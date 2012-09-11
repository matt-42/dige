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
**\file   key_press.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 16:06:54 2010
**
**\brief  key_press implementation
**
**
*/

# include <QObject>
# include <QEvent>
# include <QKeyEvent>

# include <dige/event/event.h>
# include <dige/event/key_press.h>
# include <dige/event/keycode.h>

namespace dg
{

  namespace event
  {

    key_press::key_press(keycode k, bool auto_repeat)
      : k_(k), auto_repeat_(auto_repeat)
    {
    }

    key_press::key_press()
      : k_(key_any)
    {
    }

    bool key_press::operator==(const key_press& b) const
    {
      return (b.k_ == k_ || k_ == key_any || b.k_ == key_any) && b.auto_repeat_ == auto_repeat_;
    }

    any_event make_key_press_event(QObject*, QEvent* event)
    {
      if (event->type() == QEvent::KeyPress)
      {
        QKeyEvent* e = (QKeyEvent*) event;
        // if (e->isAutoRepeat() && !auto_repeat_)
        //   return any_event();
        return key_press(qt_key_to_dige_key(e->key()), e->isAutoRepeat());
      }
      return any_event();
    }

  } // end of namespace event.

} // end of namespace dg.
