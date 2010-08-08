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
# include <SFML/System/Mutex.hpp>
# include <dige/displaylist.h>

namespace dg
{

  class EventLoopThread;

  class window
  {
  public:
    inline window(const std::string& title, unsigned width = 800, unsigned height = 600);
    inline void operator<<=(displaylist& l);

    inline void refresh();

    static inline std::map<const std::string, window*>& windows();

    inline void setupOpenGLViewport(unsigned w, unsigned h, bool lock = true);

    inline sf::Window& sf_window();

    inline void setupOpenGL();

    inline void set_active(bool pause);
    inline bool is_active();

    inline void activateThreadLoop();
    inline void deactivateThreadLoop();

    bool thread_active_;

  private:

  public:
    sf::Window* currentWindow_;
    sf::Mutex windowMutex_;
    sf::Mutex threadContextMutex_;
  private:
    EventLoopThread* loopthread_;
    displaylist dlist_;
    bool active_;
    static std::map<const std::string, window*> windows_;

    friend window& display(unsigned width, unsigned height);
    friend window& display(const std::string& title, unsigned width,
                           unsigned height);
    friend void pause();

  };

  inline window& display(unsigned width = 800, unsigned height = 600);
  inline window& display(const std::string& title, unsigned width = 800,
                         unsigned height= 600);

  inline void pause();

  extern sf::Mutex pauseMutex;

} // end of namespace dg.

# include <dige/window.hpp>

#endif
