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
**\file   gl_widget.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 25 10:02:41 2010
**
**\brief  gl_widget implemetation
**
**
*/

#include <cmath>
#include <QMouseEvent>

#include <dige/displaylist.h>
#include <dige/widgets/gl_widget.h>

#include <dige/color_picker.h>
#include <dige/panzoom.h>

namespace dg
{
  namespace widgets
  {

    gl_widget::gl_widget(displaylist& dlist, gl_widget* share)
      : QGLWidget(0, share),
        dlist_(&dlist),
        scale_(1),
        pan_(0,0),
        selected_coords_(-1, -1),
        unresizable_(false)
    {
      installEventFilter(&panzoom::instance());
      installEventFilter(&color_picker::instance());
      setMouseTracking(true);
    }

    void
    gl_widget::initializeGL()
    {
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_BLEND);
      glDisable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, 1, 0, 1, 0, 1);
      glMatrixMode(GL_MODELVIEW);
    }

    void
    gl_widget::resizeGL(int w, int h)
    {
      glViewport(0, 0, (GLint)w, (GLint)h);
    }

    void
    gl_widget::paintGL()
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glPushMatrix();
      glScalef(scale_, scale_, 1);
      glTranslatef(-pan_.x() / float(width()),
                   -pan_.y() / float(height()),
                   0);
      dlist_->draw(width(), height(), layout_);
      glPopMatrix();
    }

    QColor
    gl_widget::pick_color(unsigned x, unsigned y)
    {
      makeCurrent();
      unsigned char c[3];
      glReadPixels(x, height() - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, c);
      return QColor(c[0], c[1], c[2], 255);
    }

    point2d<float>
    gl_widget::window_to_dlist_coord(const point2d<int>& p)
    {
      return point2d<float>(p[0] / float(scale_) + pan_.x(),
                            (height() - p[1]) / float(scale_) + pan_.y());
    }

    point2d<int>
    gl_widget::window_to_image_coord(const point2d<int>& p)
    {
      if (dlist_)
        return dlist_->dlist_to_image_coord(layout_, window_to_dlist_coord(p));
      else
        return point2d<int>(0, 0);
    }

    float&
    gl_widget::scale()
    {
      return scale_;
    }

    QPointF&
    gl_widget::pan()
    {
      return pan_;
    }

    displaylist* gl_widget::dlist()
    {
      return dlist_;
    }

    void
    gl_widget::set_unresizable()
    {
      setFixedSize(size());
      unresizable_ = true;
    }

    bool
    gl_widget::unresizable() const
    {
      return unresizable_;
    }

    void
    gl_widget::mouseMoveEvent(QMouseEvent* event)
    {
      selected_coords_ = window_to_image_coord(point2d<int>(event->x(), event->y()));
      event->accept();
    }

    void
    gl_widget::mouseDoubleClickEvent(QMouseEvent* event)
    {
      selected_coords_ = window_to_image_coord(point2d<int>(event->x(), event->y()));
      event->accept();
    }

    point2d<int>
    gl_widget::selected_coords() const
    {
      return selected_coords_;
    }

  } // end of namespace widgets.

} // end of namespace dg.
