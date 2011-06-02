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
**\file   window.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Aug 21 12:53:21 2010
**
**\brief  window header.
**
**
*/

#ifndef DIGE_WINDOW_H_
# define DIGE_WINDOW_H_

# include <map>
# include <string>

# include <dige/keywords.h>
# include <dige/ui_layout.h>

class QFrame;

namespace dg
{

  /*!
  ** The window class holds a window (as a QFrame). User interface
  ** layout of a window is set using operator<<=.
  */
  class window
  {
  public:
    /*!
    ** Constructor.
    ** Initialize a new window.
    **
    ** \param title The title of the window
    ** \param width width in pixels.
    ** \param height height in pixels.
    **
    */
    window(const std::string& title, unsigned width = 800, unsigned height = 600);
    /// Destructor.
    ~window();

    /// \return width of the window.
    unsigned width() const;

    /// \return height of the window.
    unsigned height() const;

    /*!
    ** Attach the interface layout \p l to the window.
    **
    ** \param l a layout
    **
    ** \return the window.
    */
    window& operator<<=(ui_layout& l);

    /*!
    ** Set \p x to be the only item drawn on the window.
    ** This operator is just a shortcut for:
    ** window <<= hbox_start << x << hbox_end;
    **
    ** \param x Any type of widget
    **
    ** \return the window
    */
    template <typename T>
    window& operator<<=(T& x)
    {
      return *this <<= hbox_start << x << hbox_end;
    }

    /*!
    ** \return all window instances.
    */
    static const std::map<const std::string, window*>& windows();

  private:
    QFrame* currentWidget_; /*!< Underlying QFrame. */
    ui_layout ui_layout_;   /*!< Current layout. */
  };

  window& Window(const std::string& title, unsigned width, unsigned height);

} // end of namespace dg.

#endif
