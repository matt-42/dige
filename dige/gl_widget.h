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

#ifndef DIGE_GL_WIDGET_H_
# define DIGE_GL_WIDGET_H_

# include <QGLWidget>
# include <QColor>
# include <QPointF>

namespace dg
{
  class displaylist;

  class gl_widget : public QGLWidget
  {
  public:
    gl_widget(displaylist& dlist, gl_widget* share = 0);

  protected:

    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();

  public:
    QColor pick_color(unsigned x, unsigned y);

    float& scale();

    QPointF& pan();

    /// Displaylist accessor.
    displaylist* dlist();

  private:
    displaylist* dlist_;         /*!< Current displaylist. */
    float scale_;               /*!< Zoom factor. */
    QPointF pan_;             /*!< Pan. */
  };

} // end of namespace dg.

#endif
