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
**\file   shortcut_manager.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  shortcut_manager header.
**
**
*/

#ifndef DIGE_SHORTCUT_MANAGER_H_
# define DIGE_SHORTCUT_MANAGER_H_

# include <QObject>
# include <QApplication>

# include <dige/shortcuts/pause_watcher.h>
# include <dige/shortcuts/toggle_fullscreen.h>

namespace dg
{
  /// Shortcut type.
  struct shortcut { int key; void (*trigger)(); };

  /// Shortcuts bindings.
  static const shortcut shortcuts[]
    = { {Qt::Key_Space, &pause_watcher::trigger},
        {Qt::Key_F,     &toggle_fullscreen},
        {0, 0}};

  /*!
  ** Intercept keypress events to handle shortcuts.
  */
  class shortcut_manager : public QObject
  {
  public:
    /// Constructor.
    inline shortcut_manager()
    {
    }

    /*!
    ** Filter "key space release" events.
    **
    ** \param obj watched object.
    ** \param e event
    **
    ** \return true if the event has been catched.
    */
    inline bool eventFilter(QObject *obj, QEvent *e)
    {
      if (e->type() == QEvent::KeyRelease)
      {
        int key = ((QKeyEvent*)e)->key();
        for (unsigned i = 0; shortcuts[i].key; i++)
          if (shortcuts[i].key == key)
            shortcuts[i].trigger();
        return true;
      }
      else
      {
        return QObject::eventFilter(obj, e);
      }
    }
  };

  extern shortcut_manager shortcut_filter; /*!< Global shortcut manager. */

} // end of namespace dg.

#endif

