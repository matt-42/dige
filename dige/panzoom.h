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
**\file   panzoom.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  panzoom header.
**
**
*/

#ifndef DIGE_PANZOOM_H_
# define DIGE_PANZOOM_H_

# include <QObject>
# include <QPointF>

# include <dige/singleton.h>

namespace dg
{

  class gl_widget;

  /*!
  ** Panzoom.
  */
  class panzoom : public QObject, public singleton<panzoom>
  {
    friend class singleton<panzoom>;

  private:
    /// Constructor.
    panzoom();

  public:
    bool eventFilter(QObject *obj, QEvent *event);

    gl_widget* focuswidget();

  private:
    QPointF previous_pos_;
    gl_widget* focuswidget_;
  };

} // end of namespace dg.

#endif

