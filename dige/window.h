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

# include <dige/displaylist.h>

namespace dg
{
  // Forward declaration.
  class gl_widget;

  /*!
  ** The window class allow to display the content of a displaylist
  ** in an OpenGL context.
  ** It uses a thread to listen to the window event (exposure, resizing...).
  */
  class window
  {
  private:
    /*!
    ** Private Constructor.
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

  public:

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
    window& operator<<=(displaylist& l);

    /// Refresh the window content.
    void refresh();

    gl_widget* widget();

    /// Displaylist accessor.
    displaylist& dlist();

    /// Set unresizable
    void set_unresizable();

    point2d<int> selected_coords() const;

    /*!
    ** Dump the window content to \p buffer.
    ** Resize it if needed
    **
    ** \param buffer
    ** \param buffer_size
    ** \param buffer_width
    ** \param buffer_height
    **
    ** \todo The size of the buffer should stay constant even during
    ** window resizing. We may need to use opengl FBO.
    */
    void dump_rgb_frame_buffer(char*& buffer,
                                      unsigned& buffer_size,
                                      unsigned& buffer_width,
                                      unsigned& buffer_height);

    /// Associate all the created windows with theis names.
    static std::map<const std::string, window*>& windows();

  private:
    gl_widget* currentWidget_; /*!< Underlying sfml window. */
    displaylist dlist_;         /*!< Current displaylist. */

    static std::map<const std::string, window*> windows_; /*!< List all the created windows. */

    friend window& display(const std::string& title, unsigned width,
                           unsigned height);
  };

  /*!
  ** window factory. Retrieve the window named \p title. Create it if
  ** it doesn't exists.
  **
  ** \param width window width in pixel.
  ** \param height window height in pixel.
  **
  ** \return the window.
  */
  window& display(const std::string& title, unsigned width = 400,
                         unsigned height = 400);

  /*!
  ** Pause the current thread until the user press the space key in any of the
  ** window. It need at least one created window.
  */
  void pause();

} // end of namespace dg.

#endif
