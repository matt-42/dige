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
**\file   tracer_accu.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Dec 23 20:54:18 2010
**
**\brief  tracer_accu implementation
**
**
*/

# include <iostream>
# include <QtDebug>
# include <QPainterPath>
# include <QPointF>
# include <QGraphicsPathItem>

# include <dige/widgets/tracer_accu.h>

namespace dg
{

  namespace widgets
  {

    tracer_accu::tracer_accu()
      : painter_(new QPainterPath(QPointF(clock() / float(CLOCKS_PER_SEC), 0.0))),
        item_(new QGraphicsPathItem(*painter_))
    {
    }

    tracer_accu::~tracer_accu()
    {
    }


    QGraphicsPathItem*
    tracer_accu::graphic_item()
    {
      return item_.get();
    }

    QPainterPath*
    tracer_accu::painter()
    {
      return painter_.get();
    }

    void
    tracer_accu::line_to(double x, double y)
    {
      painter_->lineTo(x, y);
      item_->setPath(*painter_);
    }

    std::pair<float, float>
    tracer_accu::minmax_since(float t) const
    {
      int size = painter_->elementCount();
      int c = size - 1;

      if (!size) return std::pair<float, float>(0, 0);

      float x = t;
      float min = painter_->elementAt(c).y;
      float max = painter_->elementAt(c).y;
      while (c >= 0 && x >= t)
      {
        assert(c >= 0 && c < painter_->elementCount());
        float y = painter_->elementAt(c).y;
        if (y > max) max = y;
        if (y < min) min = y;

        x = painter_->elementAt(c).x;
        c--;
      }
      return std::pair<float, float>(min, max);
    }

  } // end of namespace widgets.

} // end of namespace dg.
