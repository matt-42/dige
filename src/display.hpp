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

#ifndef DIGE_DISPLAY_HPP_
# define DIGE_DISPLAY_HPP_

#include <iostream>
#include <SFML/Window.hpp>
#include <dige/displaylist.h>

namespace dg
{

  display::display(unsigned width, unsigned height)
  {
    if (!mainDisplay_)
    {
      sf::Window* mainWindow = new sf::Window(sf::VideoMode(width, height), "Dige window");
      mainDisplay_ = new display(*mainWindow);
    }
    currentWindow_ = mainDisplay_->currentWindow_;
    dlist_ = mainDisplay_->dlist_;

    setupOpenGL();
  }

  display::display(const std::string& title, unsigned width, unsigned height)
  {
  }

  display::display(sf::Window& window)
    : currentWindow_(&window)
  {
  }


  void display::setupOpenGLViewport(unsigned w, unsigned h)
  {
    assert(currentWindow_);
    currentWindow_->SetActive();
    glViewport(0,0, w, h);
  }

  void display::setupOpenGL()
  {
    assert(currentWindow_);
    currentWindow_->SetActive();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    setupOpenGLViewport(currentWindow_->GetWidth(), currentWindow_->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
  }

  void display::operator<<=(displaylist& l)
  {
    assert(currentWindow_);
    dlist_ = l;
    refresh();
  }

  void display::refresh()
  {
    assert(currentWindow_);
    currentWindow_->SetActive();
    dlist_.draw(currentWindow_.GetWidth(), currentWindow_.GetHeight());
    currentWindow_->Display();
  }

  display*
  display::mainDisplay()
  {
    return mainDisplay_;
  }

  sf::Window&
  display::window()
  {
    return *currentWindow_;
  }

  void pause()
  {
    assert(display::mainDisplay());
    //    assert(display::mainDisplay() || display::windows().size() > 0);

    display* display = display::mainDisplay();
    sf::Event event;
    while (true)
    {
      display->window().WaitEvent(event);
      if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
        break;
      if (event.Type == sf::Event::Resized)
      {
        std::cout << event.Size.Width << " " <<  event.Size.Height << std::endl;
        display->setupOpenGLViewport(event.Size.Width, event.Size.Height);
        display->refresh();
      }
    }
  }

} // end of namespace dg.

#endif
