// Copyright (C) 2010,2011 Matthieu Garrigues
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

#include <cstdlib>
#include <ctime>

#include <dige/dige.h>

#include "../rgb_image.h"

int main()
{
  namespace dw = dg::widgets;
  namespace de = dg::event;

  srand(time(0));
  rgb_image img(20, 20);

  // Create a window containing an ImageView named "random" that will
  // display our rgb_image.
  dg::Window("simple_image example", 500, 300) <<= dw::ImageView("random");

  unsigned t = clock();
  // Each iteration generates a random image and display it in
  // dw::ImageView("random")
  while (clock() - t < 2 * CLOCKS_PER_SEC)
  {
    for (unsigned i = 0; i < img.image_size; i++)
      img.data[i] = rand();

    // Display 3 copy of img in the ImageView.
    dw::ImageView("random")  << img << img << dw::newline
                             << img << dw::show;
  }

  // Wait for any key press event.
  de::wait_event(de::key_press());
}
