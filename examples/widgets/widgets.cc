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

// Widgets.

int main()
{
  namespace dw = dg::widgets;
  namespace de = dg::event;

  dg::Window("dige demo", 300, 300) <<=
    dg::vbox_start <<

    // Image view with dynamic size.
    dw::ImageView("test1") <<

    // Image view with static size. Not resized by window resizing.
    dw::ImageView("test2", 150, 100) <<

    // Label with text "label1".
    // Call dw::ImageView("label1").setText("another string")
    // to update label.
    dw::Label("label1") <<

    // Horizontal slider with minimum value 1, max value 100 and
    // current value at 42.
    // Slider value is retrieved by dw::Slider("slider").value().
    // Change can be monitored using dw::Slider("slider").changed_event().
    dw::Slider("slider", 1, 100, 42, dw::slider::horizontal) <<

    // Checkable button. dw::PushButton("button").is_checked() gives
    // its state.
    dw::PushButton("button1", true) <<

    // Non-checkable button. Listen to button click using
    // dw::PushButton("button2").click()
    dw::PushButton("button", false) <<

    dg::vbox_end;

  de::wait_event(de::key_press());
}
