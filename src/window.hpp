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
#include <dige/displaylist.h>

namespace dg
{

  window::window(unsigned width, unsigned height)
  {
    if (!mainWindow_)
    {
      sf::Window* mainWindow = new sf::Window(sf::VideoMode(width, height), "Dige window");
      mainWindow_ = new window(*mainWindow);
    }
    currentWindow_ = mainWindow_->currentWindow_;
    dlist_ = mainWindow_->dlist_;

    setupOpenGL();
  }

  window::window(const std::string& title, unsigned width, unsigned height)
  {
  }

  window::window(sf::Window& window)
    : currentWindow_(&window)
  {
  }


  void window::setupOpenGLViewport(unsigned w, unsigned h)
  {
    assert(currentWindow_);
    currentWindow_->SetActive();
    glViewport(0,0, currentWindow_->GetWidth(), currentWindow_->GetHeight());
  }

  void window::setupOpenGL()
  {
    assert(currentWindow_);
    currentWindow_->SetActive();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    setupOpenGLViewport(currentWindow_->GetWidth(), currentWindow_->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
  }

  void window::operator<<=(displaylist& l)
  {
    assert(currentWindow_);
    dlist_ = l;
    refresh();
  }

  void window::refresh()
  {
    assert(currentWindow_);
    currentWindow_->SetActive();
    dlist_.draw(currentWindow_->GetWidth(), currentWindow_->GetHeight());
    currentWindow_->Display();
  }

  window*
  window::mainWindow()
  {
    return mainWindow_;
  }

  sf::Window&
  window::sf_window()
  {
    return *currentWindow_;
  }


  window& display(unsigned width, unsigned height)
  {
    if (!window::mainWindow_)
      window::mainWindow_ = new window(width, height);
    return *window::mainWindow_;
  }

  void pause()
  {
    assert(window::mainWindow());
    //    assert(window::mainWindow() || window::windows().size() > 0);

    window& window = display();
    sf::Event event;
    while (true)
    {
      window.sf_window().WaitEvent(event);
      if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
        break;
      if (event.Type == sf::Event::Resized)
      {
        window.setupOpenGLViewport(event.Size.Width, event.Size.Height);
               window.refresh();
      }
           if (event.Type == sf::Event::GainedFocus)
        window.refresh();
    }
  }

} // end of namespace dg.

#endif
