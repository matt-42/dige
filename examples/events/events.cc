// Copyright (C) 2010, 2011 Matthieu Garrigues
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

// Dige includes.
#include <dige/dige.h>

int main()
{
  namespace de = dg::event;
  namespace dw = dg::widgets;

  // In order to listen to events, at least one window must be created.
  dg::Window("Event demo", 100, 100) <<=
    dg::vbox_start <<
    dw::ImageView("view") <<
    dw::PushButton("button", true) << // Checkable push button
    dg::vbox_end;

  // Block until the user release a key
  std::cout << "Press any key" << std::endl;
  de::wait_event(de::key_release());


  // Sleep until the user release key a OR key d. Events can be combined
  // with operator|
  std::cout << "Press key a or b" << std::endl;
  de::wait_event(de::key_release(de::key_a) | de::key_release(de::key_b));

  // Event based for loop.
  // Iterate after each mouse movement or release of key d until
  // escape has been released.
  // Passively wait for events between iterations.
  std::cout << "Move mouse or press d, escape to go to next step" 
            << std::endl;
  for_each_event_until(e, de::mouse_move() | de::key_release(de::key_d),
                          de::key_release(de::key_escape))
  {
    if (e == de::mouse_move())
      std::cout << "mouse move" << std::endl;
    else if (e == de::key_release(de::key_d))
      std::cout << "key d release" << std::endl;
  }

  // Non blocking event management.
  de::event_queue q(dw::PushButton("button").click() | de::key_release(de::key_a));
  de::event_queue q_esc(de::key_release(de::key_escape));

  std::cout << "Click button or press a, escape to quit" << std::endl;
  while (q_esc.is_empty())
  {
    if (!q.is_empty())
    {
      de::any_event e = q.pop_front();
      if (e == dw::PushButton("button").click())
        std::cout << "button click" << std::endl;
      if (e == de::key_release(de::key_a))
        std::cout << "key a release" << std::endl;
    }
  }

}
