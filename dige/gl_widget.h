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
# include <dige/displaylist.h>

namespace dg
{
  class gl_widget : public QGLWidget
  {
  public:
    inline gl_widget(displaylist& dlist, gl_widget* share = 0);

  protected:

    inline void initializeGL();

    inline void resizeGL(int w, int h);

    inline void paintGL();

  public:
    inline QColor pick_color(unsigned x, unsigned y);

    inline float& scale();

    inline QPointF& pan();

    /// Displaylist accessor.
    inline displaylist* dlist();

  private:
    displaylist* dlist_;         /*!< Current displaylist. */
    float scale_;               /*!< Zoom factor. */
    QPointF pan_;             /*!< Pan. */
  };

} // end of namespace dg.

# include <dige/gl_widget.hpp>

#endif
