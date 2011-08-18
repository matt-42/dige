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
**\file   image_view.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Aug 21 12:53:21 2010
**
**\brief  image_view header.
**
**
*/

#ifndef DIGE_IMAGE_VIEW_H_
# define DIGE_IMAGE_VIEW_H_

# include <map>
# include <string>

# include <dige/widgets/widget.h>
# include <dige/displaylist.h>

class QWidget;

namespace dg
{

  namespace widgets
  {

    // Forward declaration.
    class gl_widget;

    /*!
    ** The image_view class allow to display the content of a displaylist
    ** in an OpenGL context.
    */
    class image_view : public Widget<image_view>
    {
    public:
      /*!
      ** Constructor.
      ** Initialize a new image_view.
      **
      ** \param title The title of the image_view
      ** \param width width in pixels.
      ** \param height height in pixels.
      **
      */
      image_view(const std::string& title, unsigned width, unsigned height);

      /*!
      ** Constructor.
      ** Initialize a new image_view.
      **
      ** \param title The title of the image_view
      */
      image_view(const std::string& title);

      /// Destructor.
      ~image_view();

      /// \return width of the image_view.
      unsigned width() const;

      /// \return height of the image_view.
      unsigned height() const;

      /*!
      ** Set \p l to be drawn in the image_view.
      **
      ** \param l a displaylist
      **
      ** \return the image_view.
      */
      image_view& operator<<=(displaylist& l);

      template <typename T>
      image_view& operator<<(const T& i);

      image_view& operator<<(image_view& (*)(image_view&));

      /// Refresh the image_view content.
      void refresh();

      QWidget* widget() const;

      /// Displaylist accessor.
      displaylist& dlist();

      /// Load dlist images to video memory.
      void load_dlist();

      /// Set unresizable
      void set_unresizable();

      /// Newline separator.
      void newline();

      point2d<int> selected_coords() const;

      /// Unload display list from video memory.
      void unload_list();

      /*!
      ** Dump the image_view content to \p buffer.
      ** Resize it if needed
      **
      ** \param buffer
      ** \param buffer_size
      ** \param buffer_width
      ** \param buffer_height
      **
      ** \todo The size of the buffer should stay constant even during
      ** image_view resizing. We may need to use opengl FBO.
      */
      void dump_rgb_frame_buffer(unsigned char*& buffer,
                                 unsigned& buffer_size,
                                 unsigned& buffer_width,
                                 unsigned& buffer_height);

      /// Associate all the created image_views with theis names.
      static const std::map<const std::string, image_view*>& image_views();

    private:
      gl_widget* currentWidget_; /*!< Underlying qt widget. */
      displaylist dlist_;         /*!< Current displaylist. */
      bool list_on_screen_;
      friend image_view& ImageView(const std::string& title, unsigned width,
                                   unsigned height);
    };

    /*!
    ** image_view factory. Retrieve the image_view named \p
    ** title. Create it if it doesn't exists.
    ** Set the view size to width*height.
    **
    ** \param width image_view width in pixel.
    ** \param height image_view height in pixel.
    **
    ** \return the image_view.
    */
    image_view& ImageView(const std::string& title, unsigned width,
                          unsigned height);

    /*!
    ** image_view factory. Retrieve the image_view named \p
    ** title. Create it if it doesn't exists. The view size will set
    ** according to the parent window size.
    **
    **
    ** \return the image_view.
    */
    image_view& ImageView(const std::string& title);


    image_view& newline(image_view& iv);

    image_view& show(image_view& iv);

  } // end of namespace widgets.

} // end of namespace dg.

# include <dige/widgets/image_view.hpp>

#endif
