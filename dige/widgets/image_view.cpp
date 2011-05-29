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

#include <QApplication>
#include <dige/widgets/image_view.h>

#include <dige/displaylist.h>
#include <dige/named_object.h>
#include <dige/window_placer.h>
#include <dige/shortcuts/shortcut_manager.h>
#include <dige/shortcuts/pause_watcher.h>
#include <dige/pause.h>
#include <dige/widgets/gl_widget.h>
#include <dige/need_qapp.h>

namespace dg
{

  namespace widgets
  {

    image_view::image_view(const std::string& title, unsigned width, unsigned height)
    {
      need_qapp();
      if (image_views().size() == 0)
        currentWidget_ = new gl_widget(dlist_);
      else
        currentWidget_ = new gl_widget(dlist_,
                                       image_view::image_views().begin()->second->widget());

      currentWidget_->setGeometry(window_placer::place(width, height));
      currentWidget_->setWindowTitle(QString::fromStdString(title));
    }

    image_view::~image_view()
    {
      currentWidget_->makeCurrent();
      dlist_.unload();
      delete currentWidget_;
    }

    unsigned image_view::width() const
    {
      return currentWidget_->width();
    }

    unsigned image_view::height() const
    {
      return currentWidget_->height();
    }

    void
    image_view::set_unresizable()
    {
      return currentWidget_->set_unresizable();
    }

    point2d<int>
    image_view::selected_coords() const
    {
      return currentWidget_->selected_coords();
    }

    image_view& image_view::operator<<=(displaylist& l)
    {
      currentWidget_->show();
      currentWidget_->makeCurrent();
      dlist_.unload();
      dlist_ = l;
      dlist_.load();
      refresh();
      if (!pause_manager)
      {
        QApplication::processEvents();
        QApplication::sendPostedEvents();
      }
      else
        pause();

      return *this;
    }

    void image_view::refresh()
    {
      currentWidget_->updateGL();
    }

    gl_widget* image_view::widget() const
    {
      return currentWidget_;
    }

    displaylist& image_view::dlist()
    {
      return dlist_;
    }

    const std::map<const std::string, image_view*>&
    image_view::image_views()
    {
      return named_object<image_view>::instances();
    }

    void
    image_view::dump_rgb_frame_buffer(char*& buffer,
                                      unsigned& buffer_size,
                                      unsigned& buffer_width,
                                      unsigned& buffer_height)
    {
      currentWidget_->makeCurrent();

      if (int(buffer_size) < currentWidget_->width() * currentWidget_->height() * 3)
      {
        delete[] buffer;
        buffer_size = currentWidget_->width() * currentWidget_->height() * 3;
        buffer = new char[buffer_size];
      }
      if (int(buffer_height) != currentWidget_->height() ||
          int(buffer_width) != currentWidget_->width())
      {
        buffer_width = currentWidget_->width();
        buffer_height = currentWidget_->height();
      }

      glReadPixels(0, 0, currentWidget_->width(), currentWidget_->height(),
                   GL_RGB, GL_UNSIGNED_BYTE, buffer);
    }

    image_view& ImageView(const std::string& title, unsigned width, unsigned height)
    {
      return named_instance<image_view>(title, width, height);
    }

  } // end of namespace widgets.

} // end of namespace dg.
