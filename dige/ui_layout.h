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
# include <dige/widgets/widget.h>

class QBoxLayout;
class QLayout;
class QWidget;

namespace dg
{


  template <typename T>
  struct stretched_widget
  {
    stretched_widget(T& widget, unsigned stretch_factor)
      : w_(&widget),
        s_(stretch_factor)
    {
    }

    T* w_;
    unsigned s_;
  };

  struct stretched_layout;

  class ui_layout
  {
  public:
    ui_layout();

    template <typename T>
    ui_layout& operator<<(T& w);

    ui_layout& operator<<(const Literal<vbox_start_>&);
    ui_layout& operator<<(const Literal<vbox_end_>&);
    ui_layout& operator<<(const Literal<hbox_start_>&);
    ui_layout& operator<<(const Literal<hbox_end_>&);
    ui_layout& operator<<(ui_layout& l);

    template <typename T>
    ui_layout& operator<<(stretched_widget<T> e)
    {
      *this << *(e.w_);
      set_stretch_for_last_item(e.s_);
      return *this;
    }

    ui_layout& operator<<(stretched_layout e);

    void add(QWidget* w);
    void add(QLayout* l);

    QBoxLayout* root();

  private:
    void set_stretch_for_last_item(unsigned s);

    QBoxLayout* root_;
    std::stack<QBoxLayout*> stack_;
  };

  struct stretched_layout
  {
    stretched_layout(ui_layout layout, unsigned stretch_factor);

    ui_layout l_;
    unsigned s_;
  };

  namespace widgets
  {
    template <typename T>
    stretched_widget<T> operator/(Widget<T>& w, unsigned s)
    {
      T& e = exact(w);
      return stretched_widget<T>(e, s);
    }
  }

  stretched_layout operator/(ui_layout l, unsigned s);

  template <typename T>
  ui_layout& ui_layout::operator<<(T& w)
  {
    add(w.widget());
    return *this;
  }

  template <typename T, typename U>
  inline ui_layout operator<<(const Literal<T>& a, const U& b)
  {
    return ui_layout() << a << b;
  }

} // end of namespace dg.

#endif
