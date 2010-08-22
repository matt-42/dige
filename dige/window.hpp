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

#ifndef DIGE_WINDOW_HPP_
# define DIGE_WINDOW_HPP_

#include <iostream>
#include <X11/Xlib.h>
#include <SFML/Window.hpp>
#include <SFML/System/Thread.hpp>
#include <dige/displaylist.h>

namespace dg
{

  class EventLoopThread : public sf::Thread
  {
  public:
    EventLoopThread(window& w)
      : win_(w)
    {
    }

  private:
    void Run()
    {
      sf::Context context;
      sf::Event event;
      while (true)
      {
        if (win_.sf_window().WaitEvent(event))
            win_.process_event(event);
      }
    }
    window& win_;
  };

  window::window(const std::string& title, unsigned width, unsigned height)
    : loopthread_(0)
  {
    if (!xlib_thread_initialized_)
    {
      XInitThreads(); // FIXME: SHOULD BE DONE IN SFML!!!
      xlib_thread_initialized_ = true;
    }

    currentWindow_ = new sf::Window(sf::VideoMode(width, height), title);
    currentWindow_->SetActive(true);
    currentWindow_->SetFramerateLimit(0);
    setup_opengl();
    loopthread_ = new EventLoopThread(*this);
    loopthread_->Launch();
  }

  void window::setup_opengl_viewport(unsigned w, unsigned h)
  {
    assert(currentWindow_);
    glViewport(0,0, currentWindow_->GetWidth(), currentWindow_->GetHeight());
  }

  void window::process_event(sf::Event& e)
  {
    if ((e.Type == sf::Event::KeyPressed) &&
        (e.Key.Code == sf::Key::Space))
      pauseMutex.Unlock();
    if (e.Type == sf::Event::Resized)
    {
      focusMutex_.Lock();
      sf_window().SetActive(true);
      setup_opengl_viewport(e.Size.Width, e.Size.Height);
      refresh();
      sf_window().SetActive(false);
      focusMutex_.Unlock();
    }
    if (e.Type == sf::Event::GainedFocus)
    {
      focusMutex_.Lock();
      sf_window().SetActive(true);
      refresh();
      sf_window().SetActive(false);
      focusMutex_.Unlock();
    }
  }

  void window::setup_opengl()
  {
    assert(currentWindow_);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    setup_opengl_viewport(currentWindow_->GetWidth(), currentWindow_->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
  }

  window& window::operator<<=(displaylist& l)
  {
    assert(currentWindow_);

    focusMutex_.Lock();
    sf_window().SetActive(true);

    dlist_.unload();
    dlist_ = l;
    dlist_.load();
    refresh();

    sf_window().SetActive(false);
    focusMutex_.Unlock();
    return *this;
  }

  void window::refresh()
  {
    assert(currentWindow_);
    dlist_.draw(currentWindow_->GetWidth(), currentWindow_->GetHeight());
    currentWindow_->Display();
  }

  std::map<const std::string, window*>&
  window::windows()
  {
    return windows_;
  }

  const sf::Window&
  window::sf_window() const
  {
    return *currentWindow_;
  }

  sf::Window&
  window::sf_window()
  {
    return *currentWindow_;
  }

  void
  window::dump_rgb_frame_buffer(char*& buffer,
                                unsigned& buffer_size,
                                unsigned& buffer_width,
                                unsigned& buffer_height)
  {
    focusMutex_.Lock();
    sf_window().SetActive(true);

    if (buffer_size < currentWindow_->GetWidth() * currentWindow_->GetHeight() * 3)
    {
      std::cout << "resize" << std::endl;
      delete[] buffer;
      buffer_size = currentWindow_->GetWidth() * currentWindow_->GetHeight() * 3;
      buffer = new char[buffer_size];
    }
    if (buffer_height != currentWindow_->GetHeight() ||
        buffer_width != currentWindow_->GetWidth())
    {
      buffer_width = currentWindow_->GetWidth();
      buffer_height = currentWindow_->GetHeight();
    }

    glReadPixels(0, 0, currentWindow_->GetWidth(), currentWindow_->GetHeight(),
                 GL_RGB, GL_UNSIGNED_BYTE, buffer);

    sf_window().SetActive(false);
    focusMutex_.Unlock();
  }

  window& display(const std::string& title, unsigned width, unsigned height)
  {
    std::map<const std::string, window*>::const_iterator it
      = window::windows_.find(title);
    if (it != window::windows_.end())
      return *((*it).second);
    else
    {
      window* window_ = new window(title, width, height);
      window::windows_[title] = window_;
      return *window_;
    }
  }

  window& display(unsigned width, unsigned height)
  {
    return display("Dige main window", width, height);
  }

  void pause()
  {
    assert(window::windows().size() > 0);

    // Wait for space pressed.

    // Lock the pause mutex.
    pauseMutex.Lock();
    // Wait for another thread to unlock it.
    pauseMutex.Lock();
    // Then unlock it.
    pauseMutex.Unlock();

  }

} // end of namespace dg.

#endif
