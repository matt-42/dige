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
**\file   push_button.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Dec 23 20:30:09 2010
**
**\brief  Push_Button header
**
**
*/

#ifndef DIGE_PUSH_BUTTON_H_
# define DIGE_PUSH_BUTTON_H_

# include <map>
# include <string>

# include <dige/widgets/widget.h>
# include <dige/event/click.h>

// Forward declaration.
class QWidget;
class QPushButton;

namespace dg
{

  namespace widgets
  {

    /*!
    ** Classical [checkable] push button..
    */
    class push_button : public Widget<push_button>
    {
    public:
      /*!
      ** Constructor.
      ** Initialize a new push_button.
      **
      ** \param title The title of the push_button
      ** \param checkable true to set the button checkable.
      **
      */
      push_button(const std::string& title, bool checkable);

      /// Destructor.
      ~push_button();

      template <typename T>
      const T& operator()(const T& if_checked,
                          const T& if_unchecked)
      {
        return is_checked() ? if_checked : if_unchecked;
      }

      QWidget* widget() const;

      /*!
      ** Check if the button is checked.
      **
      ** \return true if it is checked.
      */
      bool is_checked();

      /*!
      ** Button click event
      **
      ** \return the event.
      */
      event::any_event click();

    private:
      QPushButton* button_;
    };

    /*!
    ** push_button factory. Retrieve the push_button named \p title. Create it if
    ** it doesn't exists.
    **
    ** \param checkable push_button checkable state.
    **
    ** \return the push_button.
    */
    push_button& PushButton(const std::string& title, bool checkable = false);

  } // end of namespace widgets.

} // end of namespace dg.

#endif
