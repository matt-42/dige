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

# include <vector>
# include <QGLWidget>
# include <QColor>
# include <QPointF>

# include <dige/displaylist.h>

namespace dg
{

  class gl_widget : public QGLWidget
  {
  public:
    gl_widget(displaylist& dlist, gl_widget* share = 0);

    point2d<int> window_to_image_coord(const point2d<int>& p);
    point2d<float> window_to_dlist_coord(const point2d<int>& p);

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

    void set_unresizable();

    bool unresizable() const;

  private:
    displaylist* dlist_;         /*!< Current displaylist. */
    std::vector<std::vector<rect2d> > layout_;       /*!< 2d layout. */
    float scale_;                /*!< Zoom factor. */
    QPointF pan_;                /*!< Pan. */
    bool unresizable_;
  };

} // end of namespace dg.

#endif
