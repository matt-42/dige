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
  ** The window class allow to display the content of a displaylist
  ** in an OpenGL context.
  ** It listen to the window event (exposure, resizing...).
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
    ** Set \p l to be drawn in the window.
    **
    ** \param l a displaylist
    **
    ** \return the window.
    */
    window& operator<<=(ui_layout& l);

    template <typename T>
    window& operator<<=(T& x)
    {
      return *this <<= hbox_start << x << hbox_end;
    }

    static const std::map<const std::string, window*>& windows();

  private:
    QFrame* currentWidget_; /*!< Underlying sfml window. */
    ui_layout ui_layout_;         /*!< Current displaylist. */
  };

  window& Window(const std::string& title, unsigned width, unsigned height);

} // end of namespace dg.

#endif
