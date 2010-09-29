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
**\file   color_picker_control.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  color_picker_control header.
**
**
*/

#ifndef DIGE_COLOR_PICKER_CONTROL_H_
# define DIGE_COLOR_PICKER_CONTROL_H_

# include <QTextStream>
# include <QPainter>
# include <QWidget>

# include <GL/gl.h>

# include <dige/singleton.h>

namespace dg
{

  /*!
  ** color_picker_control display information about a color.
  */
  class color_picker_control : public QWidget, public singleton<color_picker_control>
  {
  public:
    friend class singleton<color_picker_control>;

    /*!
    ** Place the color_picker_control window under the cursor.
    **
    ** \param e a mouse event.
    */
    void place(QMouseEvent* e);

    /*!
    ** Update color and position.
    **
    ** \param p a position.
    ** \param c a color.
    */
    void update(QPoint p, QPoint image_p, QColor c);

    /*!
    ** Draw the window content.
    */
    void paintEvent(QPaintEvent *);

  private:
    /*!
    ** Constructor. Build the window.
    */
    color_picker_control();

    QColor color_;              /*!< current color. */
    QPoint pos_;                /*!< current position. */
    QPoint image_pos_;                /*!< current image coordinates. */

    static const unsigned width_ = 170;
    static const unsigned height_ = 40;
  };

} // end of namespace dg.

#endif
