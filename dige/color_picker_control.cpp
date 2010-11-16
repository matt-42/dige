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
**\file   color_picker_control.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  color_picker_control implemetation.
**
**
*/

#include <QApplication>
#include <QTextStream>
#include <QPainter>
#include <QPaintEvent>
#include <QDesktopWidget>

#include <dige/color_picker_control.h>

namespace dg
{

  color_picker_control::color_picker_control()
    : QWidget(0, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint |
              Qt::X11BypassWindowManagerHint)
  {
    setFocusPolicy(Qt::NoFocus);
    resize(200, 200);
    show();
  }

  void
  color_picker_control::place(QMouseEvent* e)
  {
    QRect s = QApplication::desktop()->availableGeometry();
    int l = e->globalX() + 20;
    int b = e->globalY() + 20;

    if (l + int(width_) >= int(s.width()))
      l -= width_ + 40;
    if (b + int(height_) > int(s.height()))
      b -= height_ + 40;

    setGeometry(l, b, width_, height_);
    show();
  }

  void
  color_picker_control::update(QPoint p, QPoint image_p, QColor c)
  {
    pos_ = p;
    image_pos_ = image_p;
    color_ = c;
    QWidget::update();
  }

  void
  color_picker_control::paintEvent(QPaintEvent *)
  {
    QPainter painter(this);
    painter.setBrush(color_);
    painter.drawRect(0, 0, height(), height());
    painter.end();

    QPainter writer(this);
    writer.setPen(Qt::black);
    writer.setFont(QFont("Helvetica", 9));
    QString text;
    QTextStream ss(&text);
    ss << '(' << pos_.x() << ", " << pos_.y() << ")";
    if (image_pos_.x() >= 0)
      ss << " (" << image_pos_.x() << ", " << image_pos_.y() << ")";
    ss << "\nrgb(" << color_.red() << ", " << color_.green()
       << ", " << color_.blue() <<  ")";
    writer.drawText(QRect(height() + 10, 0,
                          width() - height() - 10, height()), Qt::AlignLeft,
                    text);
  }

} // end of namespace dg.
