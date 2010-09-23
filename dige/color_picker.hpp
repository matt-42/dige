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

#ifndef DIGE_COLOR_PICKER_HPP_
# define DIGE_COLOR_PICKER_HPP_

# include <QTextStream>
# include <QPainter>
# include <QWidget>

# include <GL/gl.h>

# include <dige/color_picker.h>

namespace dg
{

  color_picker::color_picker()
    : QWidget(0, Qt::FramelessWindowHint)
  {
    resize(200, 200);
    show();
  }

  void
  color_picker::place(QMouseEvent* e)
  {
    QRect s = QApplication::desktop()->availableGeometry();
    unsigned l = e->globalX() + 20;
    unsigned b = e->globalY() + 20;

    if (l + width_ >= s.width())
      l -= width_ + 40;
    if (b + height_ > s.height())
      b -= height_ + 40;

    setGeometry(l, b, width_, height_);
    show();
  }

  void
  color_picker::update(QPoint p, QColor c)
  {
    pos_ = p;
    color_ = c;
    QWidget::update();
  }

  void
  color_picker::paintEvent(QPaintEvent *)
  {
    QPainter painter(this);
    painter.setBrush(color_);
    painter.drawRect(0, 0, height(), height());
    painter.end();

    QPainter writer(this);
    writer.setPen(Qt::black);
    writer.setFont(QFont("Helvetica", 10));
    QString text;
    QTextStream ss(&text);
    ss << '(' << pos_.x() << ", " << pos_.y() << ")\n"
       << "rgb(" << color_.red() << ", " << color_.green()
       << ", " << color_.blue() <<  ")";
    writer.drawText(QRect(height() + 10, 0,
                          width() - height() - 10, height()), Qt::AlignLeft,
                    text);
  }

} // end of namespace dg.

# include <dige/color_picker.hpp>

#endif
