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

#ifndef DIGE_WINDOW_H_
# define DIGE_WINDOW_H_

# include <map>
# include <SFML/Window.hpp>
# include <dige/displaylist.h>

namespace dg
{

  class window
  {
  public:
    window(unsigned width = 800, unsigned height = 600);
    window(const std::string& title, unsigned width = 800, unsigned height = 600);
    window(sf::Window& window);

    void operator<<=(displaylist& l);

    void refresh();

    static window* mainWindow();
    static std::map<const std::string, sf::Window*>& windows();

    void setupOpenGLViewport(unsigned w, unsigned h);

    sf::Window& sf_window();

  private:
    void setupOpenGL();

    sf::Window* currentWindow_;
    displaylist dlist_;
    static window* mainWindow_;
    static std::map<const std::string, window*> windows_;

    friend window& display(unsigned width, unsigned height);
  };

  window* window::mainWindow_ = 0;

  window& display(unsigned width = 800, unsigned height = 600);

  void pause();

} // end of namespace dg.

# include <dige/window.hpp>

#endif
