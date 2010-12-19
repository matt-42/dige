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
**\file   ui_layout.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Dec 12 17:55:44 2010
**
**\brief  Ui_Layout header
**
**
*/

#ifndef DIGE_UI_LAYOUT_H_
# define DIGE_UI_LAYOUT_H_

# include <stack>
# include <boost/shared_ptr.hpp>
# include <dige/keywords.h>

class QBoxLayout;
class QWidget;

namespace dg
{

  class ui_layout
  {
  public:
    ui_layout();

    template <typename T>
    ui_layout& operator-(T& w);

    ui_layout& operator-(const vbox_start_);
    ui_layout& operator-(const vbox_end_);
    ui_layout& operator-(const hbox_start_);
    ui_layout& operator-(const hbox_end_);

    void add(QWidget* w);
    QBoxLayout* root();

  private:
    QBoxLayout* root_;
    std::stack<QBoxLayout*> stack_;
  };

  template <typename T>
  ui_layout& ui_layout::operator-(T& w)
  {
    add(w.widget());
    return *this;
  }

  template <typename T>
  ui_layout operator-(const vbox_start_ x, T& e)
  {
    return ui_layout() - x - e;
  }

  template <typename T>
  ui_layout operator-(const vbox_end_ x, T& e)
  {
    return ui_layout() - x - e;
  }

  template <typename T>
  ui_layout operator-(const hbox_start_ x, T& e)
  {
    return ui_layout() - x - e;
  }

  template <typename T>
  ui_layout operator-(const hbox_end_ x, T& e)
  {
    return ui_layout() - x - e;
  }

} // end of namespace dg.

#endif
