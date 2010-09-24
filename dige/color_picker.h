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
**\file   color_picker.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  color_picker header.
**
**
*/

#ifndef DIGE_COLOR_PICKER_H_
# define DIGE_COLOR_PICKER_H_

# include <QObject>
# include <QApplication>

# include <dige/singleton.h>
# include <dige/gl_widget.h>
# include <dige/color_picker_control.h>

namespace dg
{

  /*!
  ** Color_Picker.
  */
  class color_picker : public QObject, public singleton<color_picker>
  {
  private:
    /// Constructor.
    inline color_picker()
    {
    }

  public:
    friend class singleton<color_picker>;

    /*!
    ** Filter color_picker events.
    **
    ** \param obj watched object.
    ** \param e event
    **
    ** \return true if the event has been catched.
    */
    inline bool eventFilter(QObject *obj, QEvent *event)
    {
      gl_widget* w = (gl_widget*)(obj);

      if (event->type() == QEvent::MouseButtonPress ||
          event->type() == QEvent::MouseMove)
      {
        QMouseEvent* e = (QMouseEvent*) event;
        if (!(e->buttons() & Qt::RightButton))
          return false;
        if (e->x() < 0 || e->y() < 0 ||
            e->x() >= w->width() || e->y() >= w->height())
          color_picker_control::instance().hide();
        else
        {
          color_picker_control::instance().place(e);
          color_picker_control::instance().update(QPoint(e->x(), e->y()),
                                                  QColor(w->pick_color(e->x(), e->y())));
          //w->activateWindow();
        }
        return true;
      }
      if (event->type() == QEvent::MouseButtonRelease)
      {
        color_picker_control::instance().hide();
        return true;
      }

      return false;
    }
  };

} // end of namespace dg.

#endif

