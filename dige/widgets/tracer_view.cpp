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
**\file   tracer_view.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Jan  2 19:31:39 2011
**
**\brief  tracer_view implementation
**
**
*/

# include <QDebug>
# include <QGLWidget>
# include <dige/widgets/tracer_view.h>

namespace dg
{

  namespace widgets
  {

    tracer_view::tracer_view(QGraphicsScene* s)
      : QGraphicsView(s),
        dt_(1),
        dy_(1)
    {
      setAlignment(Qt::AlignLeft);
      //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      //setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
      //view_->setViewport(new QGLWidget());
    }

    void tracer_view::set_view_dtime(float f)
    {
      dt_ = f;
    }

    void tracer_view::set_view_dy(float f)
    {
      dy_ = f;
    }

    float tracer_view::dt()
    {
      return dt_;
    }

    float tracer_view::dy()
    {
      return dy_;
    }

    void tracer_view::update_scale()
    {
      resetMatrix();
      scale(width() / dt_, height() / dy_);
    }

    void tracer_view::resizeEvent(QResizeEvent*)
    {
      update_scale();
    }

  } // end of namespace widgets.

} // end of namespace dg.
