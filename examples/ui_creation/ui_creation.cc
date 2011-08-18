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

#include <dige/dige.h>

// GUI creation with Dige.

int main()
{
  namespace dw = dg::widgets;
  namespace de = dg::event;

  // Stand alone window named "testalone" that contains one image view.
  dw::ImageView("testalone");

  // Two vertically aligned image views in one window named "dige demo".
  dg::Window("dige demo", 300, 300) <<=
    dg::vbox_start <<
    dw::ImageView("test1") <<
    dw::ImageView("test2") <<
    dg::vbox_end;

  // Two horizontally aligned image views in one window named "dige demo".
  // test1 will be twice larger than test2
  dg::Window("proportions", 300, 300) <<=
    dg::hbox_start <<
    dw::ImageView("test3") % 2 <<  // Use operator % to set proportions of widget.
    dw::ImageView("test4") % 1 <<
    dg::hbox_end;

  // image view size can be fixed.
  dg::Window("Fixed size", 300, 300) <<=
    dg::vbox_start <<
    dw::ImageView("test5", 100, 20) << // Fixed size image view
    dw::ImageView("test6") << // Dynamically sized image view that expands to fill the window.
    dg::vbox_end;

  // Boxes can be nested.
  dg::Window("Nested layouts", 300, 300) <<=

    dg::hbox_start << // Main horizontal layout.

    (  dg::vbox_start << // First vertical sub layout.
       dw::Label("label7") <<
       dw::ImageView("test7") <<
       dg::vbox_end
    ) <<
    (  dg::vbox_start << // Second vertical sub layout.
       dw::Label("label8") <<
       dw::ImageView("test8") <<
       dg::vbox_end
    ) <<

    dg::hbox_end;

  de::wait_event(de::key_press());
}
