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

#ifndef DIGE_GL_WIDGET_HPP_
# define DIGE_GL_WIDGET_HPP_

# include <dige/displaylist.h>
# include <dige/gl_widget.h>
# include <dige/color_picker.h>
# include <dige/panzoom.h>

namespace dg
{
  gl_widget::gl_widget(displaylist& dlist, gl_widget* share)
    : QGLWidget(0, share),
      dlist_(&dlist),
      scale_(1),
      pan_(0,0)
  {
    installEventFilter(&panzoom::instance());
    installEventFilter(&color_picker::instance());
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
    glTranslatef(- pan_.x() / float(width()),
                 - pan_.y() / float(height()),
                 0);
    dlist_->draw(width(), height());
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

} // end of namespace dg.

#endif
