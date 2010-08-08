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
        win_.sf_window().WaitEvent(event);
        if (win_.thread_active_)
        {
          win_.threadContextMutex_.Lock();
          win_.sf_window().SetActive(true);

          if ((event.Type == sf::Event::KeyPressed) &&
              (event.Key.Code == sf::Key::Space))
            pauseMutex.Unlock();
          if (event.Type == sf::Event::Resized)
          {
            win_.setupOpenGLViewport(event.Size.Width, event.Size.Height, true);
            win_.refresh();
          }
          if (event.Type == sf::Event::GainedFocus)
          {
            win_.refresh();
          }
          win_.sf_window().SetActive(false);
          win_.threadContextMutex_.Unlock();
        }
      }
    }

    window& win_;
  };

  window::window(const std::string& title, unsigned width, unsigned height)
    : loopthread_(0),
      active_(false),
      thread_active_(false)
  {
    currentWindow_ = new sf::Window(sf::VideoMode(width, height), title);
    currentWindow_->SetActive(true);
    setupOpenGL();
    loopthread_ = new EventLoopThread(*this);
    loopthread_->Launch();
  }

  void window::setupOpenGLViewport(unsigned w, unsigned h, bool lock)
  {
    assert(currentWindow_);
    glViewport(0,0, currentWindow_->GetWidth(), currentWindow_->GetHeight());
  }

  void window::setupOpenGL()
  {
    assert(currentWindow_);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    setupOpenGLViewport(currentWindow_->GetWidth(), currentWindow_->GetHeight(), false);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
  }

  void window::operator<<=(displaylist& l)
  {
    assert(currentWindow_);
    dlist_.unload();
    dlist_ = l;
    dlist_.load();
    refresh();
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

  sf::Window&
  window::sf_window()
  {
    return *currentWindow_;
  }

  void
  window::set_active(bool active)
  {
    //    if (active)
    //  currentWindow_->SetActive(false);
    active_ = active;
  }


  void
  window::activateThreadLoop()
  {
    currentWindow_->SetActive(false);
    thread_active_ = true;
  }

  void
  window::deactivateThreadLoop()
  {
    thread_active_ = false;
    threadContextMutex_.Lock();
    threadContextMutex_.Unlock();
    currentWindow_->SetActive(true);
  }

  bool
  window::is_active()
  {
    return active_;
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

    // Start event loop thread of each opened window.
    for (std::map<const std::string, window*>::const_iterator it
      = window::windows().begin(); it != window::windows().end(); it++)
      it->second->activateThreadLoop();

    // Wait for space pressed.
    pauseMutex.Lock();
    pauseMutex.Lock();
    pauseMutex.Unlock();

    // Then we can stop the thread loops.
    for (std::map<const std::string, window*>::const_iterator it
      = window::windows().begin(); it != window::windows().end(); it++)
      it->second->deactivateThreadLoop();
  }

} // end of namespace dg.

#endif
