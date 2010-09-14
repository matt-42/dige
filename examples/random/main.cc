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

// Dige includes.
#include <dige/window.h>
#include <dige/image.h>

// A simple rgb image type
struct rgb_image
{
  rgb_image(unsigned w, unsigned h)
    : width(w),
      height(h),
      image_size(w * h * 3)
  {
    data = new unsigned char[image_size];
  }

  ~rgb_image()
  {
    delete data;
  }

  unsigned width;
  unsigned height;
  unsigned image_size;
  unsigned char* data;
};

namespace dg
{
  // Adapt our rgb_image type into the dige image type.
  image<trait::format::rgb, unsigned char>
  adapt(const rgb_image& i)
  {
    return image<trait::format::rgb, unsigned char>
      (i.width, i.height, i.data);
  }
}

int main()
{
  using dg::display; // Dige display.
  using dg::dl; // Dige list starter

  srand(time(0));
  rgb_image img(200, 200);

  unsigned t = clock();
  while (clock() - t < 5 * CLOCKS_PER_SEC)
  {
    for (unsigned i = 0; i < img.image_size; i++)
      img.data[i] = rand();

    // Display in a 300*200 window called "random" 3 copy of our image.
    // It will looks like:
    //
    //  |-------------|
    //  | img     img |
    //  |             |
    //  |             |
    //  |     img     |
    //  |-------------|
    //
    display("random", 300, 200)
      <<= dl() - img - img +
                    img;
  }

  // Pause the program on the last image.
  dg::pause();
}
