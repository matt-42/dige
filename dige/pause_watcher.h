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
**\file   pause_watcher.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  pause_watcher header.
**
**
*/

#ifndef DIGE_PAUSE_WATCHER_H_
# define DIGE_PAUSE_WATCHER_H_

#include <QObject>

namespace dg
{
  /*!
  ** Intercept keypress event to handle pauses when the user press
  ** space.
  */
  class pause_watcher : public QObject
  {
  public:
    /// Constructor.
    inline pause_watcher()
      : pause_(false)
    {
    }

    /*!
    ** pause_ setter.
    **
    ** \param p true to set it paused.
    */
    inline void set(bool p)
    {
      pause_ = p;
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
      if (e->type() == QEvent::KeyRelease && ((QKeyEvent*)e)->key() == Qt::Key_Space)
      {
        pause_ = !pause_;
        return true;
      }
      else
      {
        return QObject::eventFilter(obj, e);
      }
    }

    /*!
    ** Bool conversion
    **
    ** \return true if paused.
    */
    inline operator bool() const
    {
      return pause_;
    }

    /*!
    ** Bool conversion
    **
    ** \return false if paused.
    */
    inline bool operator !() const
    {
      return !pause_;
    }

  private:
    bool pause_;                /*!< True if paused. */
  };

  extern pause_watcher pause_manager; /*!< Global pause manager. */

} // end of namespace dg.

#endif

