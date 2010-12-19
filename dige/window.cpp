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

#include <QApplication>
#include <QFrame>
#include <iostream>

#include <dige/window.h>

#include <dige/named_object.h>
#include <dige/window_placer.h>
#include <dige/need_qapp.h>

namespace dg
{
  QRect window_placer::screen_(0,0,0,0);

  window::window(const std::string& title, unsigned width, unsigned height)
  {
    need_qapp();

    currentWidget_ = new QFrame();

    currentWidget_->setGeometry(window_placer::place(width, height));
    currentWidget_->setWindowTitle(QString::fromStdString(title));
    currentWidget_->show();
  }

  window::~window()
  {
    delete currentWidget_;
  }

  unsigned window::width() const
  {
    return currentWidget_->width();
  }

  unsigned window::height() const
  {
    return currentWidget_->height();
  }

  window& window::operator<<=(ui_layout& l)
  {
    ui_layout_ = l;
    currentWidget_->setLayout((QLayout*)l.root());
    return *this;
  }

  const std::map<const std::string, window*>&
  window::windows()
  {
    return named_object<window>::instances();
  }

  window& Window(const std::string& title, unsigned width, unsigned height)
  {
    return named_instance<window>(title, width, height);
  }

} // end of namespace dg.
