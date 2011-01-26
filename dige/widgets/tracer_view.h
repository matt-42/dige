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
**\file   tracer_view.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Jan  2 19:31:50 2011
**
**\brief  tracer_view header.
**
**
*/

#ifndef DIGE_TRACER_VIEW_H_
# define DIGE_TRACER_VIEW_H_

# include <QGraphicsView>
# include <QResizeEvent>
# include <QGraphicsScene>

namespace dg
{

  /*!
  ** Fixme
  */
  class tracer_view : public QGraphicsView
  {
  public:
    /*!
    ** Constructor.
    ** Initialize a new tracer_view.
    */
    tracer_view(QGraphicsScene* s);

    void set_view_dtime(float dt);
    void set_view_dy(float dy);

    float dt();
    float dy();

    void update_scale();

  protected:
    void resizeEvent(QResizeEvent* event);

    float dt_;
    float dy_;
  };

} // end of namespace dg.

#endif
