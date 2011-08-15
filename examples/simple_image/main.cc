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

// Our simple rgb image type
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
    delete[] data;
  }

  unsigned width;
  unsigned height;
  unsigned image_size;
  unsigned char* data;
};

namespace dg
{

  // We then define the bridge between our custom rgb_image type and the
  // internal dg::image type. This will be called before displaying each
  // rgb_image. dg::image takes two template parameters:
  //
  // 1> The format of the pixels which can be : - trait::format::rgb
  //                                            - trait::format::rgba
  //                                            - trait::format::luminance
  //     Or, if your opengl version supports it:
  //                                            - trait::format::bgr
  //                                            - trait::format::bgra
  // 2> The data type which can be: float, char, short, int,
  //    unsigned float, unsigned char, unsigned short, unsigned int.
  // Note that when displaying float, values has to be normalized between
  // 0 and 1.
  image<trait::format::rgb, unsigned char>
  adapt(const ::rgb_image& i)
  {
    return image<trait::format::rgb, unsigned char>
      (i.width, i.height, i.data);
    // Warning: dg::image only handles contiguous buffers of pixel.
  }

}

int main()
{
  namespace dw = dg::widgets;
  namespace de = dg::event;
  using dg::dl; // image list starter.

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

    // Display img 3 times in the ImageView. 
    // dl() starts a list of images.
    dw::ImageView("random")  <<= dl() - img - img + img;
  }

  // Wait for any key press event.
  de::wait_event(de::key_press());
}
