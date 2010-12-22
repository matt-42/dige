// Dige includes.
#include <dige/window.h>
#include <dige/widgets/image_view.h>
#include <dige/image.h>
#include <dige/pick_coords.h>
#include <dige/event/wait.h>
#include <dige/event/mouse_move.h>
#include <dige/event/key_release.h>

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
    delete[] data;
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
  using namespace dg;

  rgb_image img(200, 200);

  for (unsigned i = 0; i < img.image_size; i++)
    img.data[i] = 0;


  dg::Window("Event demo [Press enter to exit]", 500, 500) <<=
    (dg::hbox_start -
     display("event") -
     dg::hbox_end);

  display("event") <<= dl() - img;

  for_each_event_until(e, dg::mouse_move() | dg::key_release(dg::key_d),
                       dg::key_release(dg::key_return))
  {
    int x = 0, y = 0;
    dg::pick_coords("event", x, y);
    if (e == dg::mouse_move())
      img.data[y * 200 * 3 + x * 3 + 0] = 255;
    else if (e == dg::key_release(dg::key_d))
      img.data[y * 200 * 3 + x * 3 + 0] = 0;

    display("event") <<= dl() - img;
  }
}
