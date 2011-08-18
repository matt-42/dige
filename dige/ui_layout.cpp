// Copyright (C) 2010, 2011 Matthieu Garrigues
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
**\file   ui_layout.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Dec 12 18:10:28 2010
**
**\brief  ui_layout implementation.
**
**
*/

#include <QHBoxLayout>
#include <QWidget>
#include <dige/ui_layout.h>
#include <dige/need_qapp.h>

namespace dg
{

  ui_layout::ui_layout()
    : root_(new QHBoxLayout()),
      sf_(1)
  {
    need_qapp();

    root_->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding,
                                         QSizePolicy::Expanding));
    stack_.push(root_);
  }

  ui_layout& ui_layout::operator<<(const Literal<vbox_start_>&)
  {
    QBoxLayout* l = stack_.top();
    QVBoxLayout* n = new QVBoxLayout();
    n->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding,
                                     QSizePolicy::Expanding));

    l->addLayout(n, 1);
    stack_.push(n);
    return *this;
  }

  ui_layout& ui_layout::operator<<(const Literal<vbox_end_>&)
  {
    stack_.pop();
    return *this;
  }

  ui_layout& ui_layout::operator<<(const Literal<hbox_start_>&)
  {
    QBoxLayout* l = stack_.top();
    QHBoxLayout* n = new QHBoxLayout();
    n->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding,
                                     QSizePolicy::Expanding));

    l->addLayout(n, 1000);
    set_stretch_for_last_item(1);
    stack_.push(n);
    return *this;
  }

  ui_layout& ui_layout::operator<<(const Literal<hbox_end_>&)
  {
    stack_.pop();
    return *this;
  }

  ui_layout& ui_layout::operator<<(const ui_layout& n)
  {
    QBoxLayout* l = stack_.top();
    l->addLayout(n.root(), n.sf_);
    return *this;
  }

  void ui_layout::add(QWidget* w)
  {
    stack_.top()->addWidget(w, 1000);
    set_stretch_for_last_item(1);
  }

  void ui_layout::add(QLayout* l)
  {
    stack_.top()->addLayout(l);
  }

  QBoxLayout* ui_layout::root() const
  {
    return root_;
  }

  void ui_layout::set_stretch_for_last_item(unsigned s)
  {
    QBoxLayout* l = stack_.top();
    l->setStretch(l->count() - 1, s);
  }

  void ui_layout::set_stretch(unsigned sf)
  {
    sf_ = sf;
  }

  ui_layout& ui_layout::operator%(unsigned sf)
  {
    sf_ = sf;
    return *this;
  }

} // end of namespace dg.
