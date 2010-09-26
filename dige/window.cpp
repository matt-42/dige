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
#include <dige/window.h>

#include <dige/displaylist.h>
#include <dige/window_placer.h>
#include <dige/shortcuts/shortcut_manager.h>
#include <dige/shortcuts/pause_watcher.h>
#include <dige/gl_widget.h>

namespace dg
{
  std::map<const std::string, window*> window::windows_;
  QRect window_placer::screen_(0,0,0,0);


  window::window(const std::string& title, unsigned width, unsigned height)
  {
    if (window::windows().size() == 0)
    {
      static const char* dumy_argv = "";
      static int dumy_argc = 1;
      QApplication* app = new QApplication(dumy_argc, (char**)&dumy_argv);
      currentWidget_ = new gl_widget(dlist_);
    }
    else
    {
      currentWidget_ = new gl_widget(dlist_,
                                     window::windows().begin()->second->widget());
    }

    currentWidget_->setGeometry(window_placer::place(width, height));
    currentWidget_->setWindowTitle(QString::fromStdString(title));

    if (window::windows().size() == 0)
    {
      currentWidget_->grabKeyboard();
      currentWidget_->installEventFilter(&shortcut_filter);
    }

  }

  window::~window()
  {
    currentWidget_->makeCurrent();
    dlist_.unload();
    delete currentWidget_;
  }

  unsigned window::width() const
  {
    return currentWidget_->width();
  }

  unsigned window::height() const
  {
    return currentWidget_->height();
  }

  window& window::operator<<=(displaylist& l)
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

  void window::refresh()
  {
    currentWidget_->updateGL();
  }

  gl_widget* window::widget()
  {
    return currentWidget_;
  }

  displaylist& window::dlist()
  {
    return dlist_;
  }

  std::map<const std::string, window*>&
  window::windows()
  {
    return windows_;
  }

  void
  window::dump_rgb_frame_buffer(char*& buffer,
                                unsigned& buffer_size,
                                unsigned& buffer_width,
                                unsigned& buffer_height)
  {
    currentWidget_->makeCurrent();

    if (buffer_size < currentWidget_->width() * currentWidget_->height() * 3)
    {
      delete[] buffer;
      buffer_size = currentWidget_->width() * currentWidget_->height() * 3;
      buffer = new char[buffer_size];
    }
    if (buffer_height != currentWidget_->height() ||
        buffer_width != currentWidget_->width())
    {
      buffer_width = currentWidget_->width();
      buffer_height = currentWidget_->height();
    }

    glReadPixels(0, 0, currentWidget_->width(), currentWidget_->height(),
                 GL_RGB, GL_UNSIGNED_BYTE, buffer);
  }

  window& display(const std::string& title, unsigned width, unsigned height)
  {
    std::map<const std::string, window*>::const_iterator it
      = window::windows_.find(title);
    if (it != window::windows_.end())
    {
      window* win = (*it).second;
      return *((*it).second);
    }
    else
    {
      window* window_ = new window(title, width, height);
      window::windows_[title] = window_;
      return *window_;
    }
  }

  void pause()
  {
    assert(window::windows().size() > 0);

    pause_manager.set(true);
    while (pause_manager)
    {
      QApplication::processEvents(QEventLoop::WaitForMoreEvents);
      QApplication::sendPostedEvents();
    }
  }

} // end of namespace dg.
