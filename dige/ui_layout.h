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

  /*!
  ** Holds a widget with its stretch factor to be used during
  ** its insertion in a hbox or vbox layout.
  ** See Qt documentation for more infos on Qt Layout system.
  */
  template <typename T>
  struct stretched_widget
  {
    /*!
    ** Constructor
    **
    ** \param widget The widget.
    ** \param stretch_factor stretch factor.
    */
    stretched_widget(T& widget, unsigned stretch_factor)
      : w_(&widget),
        s_(stretch_factor)
    {
    }

    T* w_;                      /*!< The widget. */
    unsigned s_;                /*!< Stretch factor. */
  };

  /// Forward declaration.
  struct stretched_layout;

  /*!
  ** Class ui_layout use Qt layouts to build and hold the layout tree of a
  ** graphical user interface.
  **
  */
  class ui_layout
  {
  public:
    /// Constructor
    ui_layout();

    /// Operators that dynamically build the interface.
    //@{
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
    //@}

    /// Root layout accessor.
    QBoxLayout* root();

  private:
    void set_stretch_for_last_item(unsigned s);

    QBoxLayout* root_;          /*!< Root layout. */
    std::stack<QBoxLayout*> stack_; /*!< Stack of layout. */
  };

  /*!
  ** Holds a layout with its stretch factor to be used during
  ** its insertion in a parent hbox or vbox layout.
  ** See Qt documentation for more infos on Qt Layout system.
  */
  struct stretched_layout
  {
    /*!
    ** Constructor
    **
    ** \param widget The layout.
    ** \param stretch_factor stretch factor.
    */
    stretched_layout(ui_layout layout, unsigned stretch_factor);

    ui_layout l_;               /*!< The layout. */
    unsigned s_;                /*!< Stretch factor. */
  };

  namespace widgets
  {
    /*!
    ** This operator annotates a widget with a stretch factor.
    **
    ** \param w a widget.
    ** \param s the stretch factor.
    **
    ** \return The stretched_widget.
    */
    template <typename T>
    stretched_widget<T> operator/(Widget<T>& w, unsigned s)
    {
      T& e = exact(w);
      return stretched_widget<T>(e, s);
    }
  }

  /*!
  ** This operator annotates a layout with a stretch factor.
  **
  ** \param l a layout.
  ** \param s the stretch factor.
  **
  ** \return The stretched_layout.
  */
  stretched_layout operator/(ui_layout l, unsigned s);

  template <typename T>
  ui_layout& ui_layout::operator<<(T& w)
  {
    add(w.widget());
    return *this;
  }

  /*!
  ** Initiate a ui_layout in a layout defined with operator<<.
  **
  ** \param a A literal ([h|v]box_[start|end]).
  ** \param b Any type of widget or layout.
  **
  ** \return the ui_layout.
  */
  template <typename T, typename U>
  inline ui_layout operator<<(const Literal<T>& a, const U& b)
  {
    return ui_layout() << a << b;
  }

} // end of namespace dg.

#endif
