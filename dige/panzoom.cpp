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
**\file   panzoom.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 12422:37:43 2010
**
**\brief  panzoom implementation.
**
**
*/

#include <QObject>
#include <QEvent>
#include <QWheelEvent>
#include <QMouseEvent>

#include <dige/panzoom.h>
#include <dige/panzoom_control.h>
#include <dige/widgets/gl_widget.h>

//#define WITH_PANZOOM_CTRL

namespace dg
{
  panzoom::panzoom()
    : focuswidget_(0)
  {
  }

  bool
  panzoom::eventFilter(QObject *obj, QEvent *event)
  {
    widgets::gl_widget* w = dynamic_cast<widgets::gl_widget*>(obj);
    if (!w)
      return false;

    if (event->type() == QEvent::Wheel)
    {
      QWheelEvent* e = (QWheelEvent*) event;
      float c = 1. + e->delta() / 900.;
      w->pan() += QPointF(e->x() * (c-1) / (c * w->scale()),
                          float(w->height() - e->y()) * (c-1) / (c * w->scale()));
      w->scale() *= c;

      #ifdef WITH_PANZOOM_CTRL
      if (focuswidget_ != w || ! w->isActiveWindow())
        panzoom_control::instance().place(w);
      else
        panzoom_control::instance().update(w);
      #endif

      focuswidget_ = w;
      w->updateGL();
      return true;
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
      QMouseEvent* e = (QMouseEvent*) event;
      previous_pos_ = e->posF();
      if (w->scale() == 1 && w->pan() == QPointF(0,0))
        return false;

      #ifdef WITH_PANZOOM_CTRL
      if (focuswidget_ != w)
        panzoom_control::instance().place(w);
      else
      {
        panzoom_control::instance().update(w);
        panzoom_control::instance().activateWindow();
        w->activateWindow();
      }
      #endif

      focuswidget_ = w;
      return true;
    }

    if (event->type() == QEvent::MouseMove)
    {
      QMouseEvent* e = (QMouseEvent*) event;
      if (!(e->buttons() & Qt::LeftButton))
        return false;

      if (focuswidget_ != w)
        previous_pos_ = e->posF();

      QPointF delta = e->posF() - previous_pos_;
      previous_pos_ = e->posF();

      w->pan() -= QPointF(delta.x() / w->scale(),
                          -delta.y() / w->scale());
      #ifdef WITH_PANZOOM_CTRL
      panzoom_control::instance().update(w);
      #endif
      w->updateGL();
      focuswidget_ = w;
      return true;
    }

    if (event->type() == QEvent::Resize ||
        event->type() == QEvent::Move ||
        event->type() == QEvent::DragMove)
    {
      if (w->scale() == 1 && w->pan() == QPointF(0,0))
        return false;
      #ifdef WITH_PANZOOM_CTRL
      panzoom_control::instance().place(w);
      #endif
      focuswidget_ = w;
    }

    if (event->type() == QEvent::WindowActivate)
    {
      if ((w->scale() == 1 && w->pan() == QPointF(0,0)) ||
          focuswidget_ == w)
        return false;
      #ifdef WITH_PANZOOM_CTRL
      panzoom_control::instance().place(w);
      #endif
      focuswidget_ = w;
    }

    return false;
  }

  widgets::gl_widget* panzoom::focuswidget()
  {
    return focuswidget_;
  }

} // end of namespace dg.

