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
**\file   panzoom_control.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  panzoom_control implemetation.
**
**
*/

#include <QApplication>
#include <QDesktopWidget>

#include <dige/widgets/image_view.h>
#include <dige/panzoom_control.h>

namespace dg
{

  panzoom_control::panzoom_control()
    : QGLWidget(0, static_cast<widgets::gl_widget*>
                (widgets::image_view::image_views().begin()->second->widget()),
                Qt::FramelessWindowHint),
      widget_(0)
  {
    setFocusPolicy(Qt::NoFocus);
    resize(width_, height_);
    show();
  }

  void
  panzoom_control::hide()
  {
    widget_ = 0;
    QGLWidget::hide();
  }

  void
  panzoom_control::place(widgets::gl_widget* w)
  {
    QRect s = QApplication::desktop()->availableGeometry();
    QRect wg = w->frameGeometry();

    float wi = width_;
    float he = height_;
    int l;
    int b;

    if (w->width() > w->height())
    {
      wi = width_;
      he = width_ * w->height() / float(w->width());
    }
    else
    {
      wi = height_ * w->width() / float(w->height());
      he = height_;
    }

    if (w->isFullScreen())
    {
      // setWindowFlags(Qt::FramelessWindowHint |
      //                Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
      l = 0;
      b = 0;
    }
    else
    {
      setWindowFlags(Qt::FramelessWindowHint);

      unsigned sp = 10;
      l = wg.x() - wi - sp;
      b = wg.y() - sp;

      if (l < s.x()) // go right
        l += wi + wg.width() + sp*2;
      if (l + wi >= s.width()) // go down
      {
        l = wg.x();
        b = wg.y() - he - sp;
      }
      if (b < 0) // go up
      {
        l = wg.x();
        b = wg.y() + wg.height() + sp;
      }

    }

    setGeometry(l, b, wi, he);

    widget_ = w;

    show();
    update(w);

    raise();
    activateWindow();
  }


  void
  panzoom_control::activateWindow()
  {
    if (!widget_)
      return;

    QGLWidget::activateWindow();
    widget_->activateWindow();
  }

  void
  panzoom_control::update(widgets::gl_widget* w)
  {
    if (widget_ != w)
    {
      widget_ = w;
      place(w);
    }
    updateGL();
  }

  void
  panzoom_control::initializeGL()
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
  panzoom_control::resizeGL(int w, int h)
  {
    glViewport(0, 0, (GLint)w, (GLint)h);
  }

  void
  panzoom_control::paintGL()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    if (widget_)
    {
      widget_->dlist()->draw(width(), height());
      float l = (widget_->pan().x()) / widget_->width();
      float r = (widget_->pan().x() + widget_->width() / widget_->scale()) / widget_->width();
      float b = (widget_->pan().y()) / widget_->height();
      float t = (widget_->pan().y() + widget_->height() / widget_->scale()) / widget_->height();

      glColor3f(1.,1.,1.);
      glBegin(GL_LINE_LOOP);
      glVertex2f(l, b);
      glVertex2f(l, t);
      glVertex2f(r, t);
      glVertex2f(r, b);
      glEnd();
    }

    // Widget border.
    glColor3f(1.,1.,1.);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1. / width(), 1. / height());
    glVertex2f(1. / width(), (height() - 1.) / float(height()));
    glVertex2f((width() - 1.) / float(width()), (height() - 1.) / float(height()));
    glVertex2f((width() - 1) / float(width()), 1. / height());
    glEnd();

  }

} // end of namespace dg.
