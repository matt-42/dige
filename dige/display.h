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

#ifndef DISPLAY_H_
# define DISPLAY_H_

# include <map>
# include <SFML/Window.hpp>
# include <dige/displaylist.h>

namespace dg
{

  class window
  {
  public:
    inline display(unsigned width = 800, unsigned height = 600);
    inline display(const std::string& title, unsigned width = 800, unsigned height = 600);
    inline display(sf::Window& window);

    inline void operator<<=(displaylist& l);

    inline void refresh();

    static inline display* mainDisplay();
    static inline std::map<const std::string, sf::Window*>& windows();

    inline void setupOpenGLViewport(unsigned w, unsigned h);

    inline sf::Window& window();

  private:
    inline void setupOpenGL();

    sf::Window* currentWindow_;
    displaylist dlist_;
    static display* mainDisplay_;
    static std::map<const std::string, display*> displays_;
  };

  display* display::mainDisplay_ = 0;

  void pause();

} // end of namespace dg.

# include <dige/display.hpp>

#endif
