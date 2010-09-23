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
**\file   color_picker.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  color_picker header.
**
**
*/

#ifndef DIGE_COLOR_PICKER_H_
# define DIGE_COLOR_PICKER_H_

# include <QTextStream>
# include <QPainter>
# include <QWidget>

# include <GL/gl.h>

# include <dige/singleton.h>

namespace dg
{

  /*!
  ** color_picker display information about a color.
  */
  class color_picker : public QWidget, public singleton<color_picker>
  {
  public:
    friend class singleton<color_picker>;

    /*!
    ** Place the color_picker window under the cursor.
    **
    ** \param e a mouse event.
    */
    inline void place(QMouseEvent* e);

    /*!
    ** Update color and position.
    **
    ** \param p a position.
    ** \param c a color.
    */
    inline void update(QPoint p, QColor c);

    /*!
    ** Draw the window content.
    */
    inline void paintEvent(QPaintEvent *);

  private:
    /*!
    ** Constructor. Build the window.
    */
    inline color_picker();

    QColor color_;              /*!< current color. */
    QPoint pos_;                /*!< current position. */

    static const unsigned width_ = 200;
    static const unsigned height_ = 40;
  };

} // end of namespace dg.

# include <dige/color_picker.hpp>

#endif
