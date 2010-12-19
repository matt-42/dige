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
**\file   ui_layout.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Dec 12 18:10:28 2010
**
**\brief  ui_layout implementation
**
**
*/

#include <QHBoxLayout>
#include <dige/ui_layout.h>

namespace dg
{

  ui_layout::ui_layout()
    : root_(new QHBoxLayout())
  {
    stack_.push(root_);
  }

  template <typename T>
  ui_layout& ui_layout::operator-(T& w)
  {
    stack_.top()->addWidget(w.widget());
    return *this;
  }

  ui_layout& ui_layout::operator-(const vbox_start_&)
  {
    QBoxLayout* l = stack_.top();
    QVBoxLayout* n = new QVBoxLayout();

    l->addLayout(n);
    stack_.push(n);
  }

  ui_layout& ui_layout::operator-(const vbox_end_&)
  {
    stack_.pop();
  }

  ui_layout& ui_layout::operator-(const hbox_start_&)
  {
    QBoxLayout* l = stack_.top();
    QHBoxLayout* n = new QHBoxLayout();

    l->addLayout(n);
    stack_.push(n);
  }

  ui_layout& ui_layout::operator-(const hbox_end_&)
  {
    stack_.pop();
  }

  QBoxLayout* ui_layout::root()
  {
    return root_;
  }

} // end of namespace dg.

#endif
