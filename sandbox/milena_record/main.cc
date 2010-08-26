#include <dige/window.h>
#include <dige/image.h>
#include <dige/recorder.h>
#include <dige/value_traits.h>

#include "load.hh"

#include <mln/core/image/image2d.hh>
#include <mln/value/rgb8.hh>
#include <mln/value/int_u16.hh>
#include <mln/value/rgb16.hh>
#include <mln/trait/value/comp.hh>
#include <mln/data/paste.hh>

namespace dg
{

  // Get the color format from the dimension of the color space.
  template <unsigned dim>
  struct dim_to_dige_format {};
  template <>
  struct dim_to_dige_format<1> { typedef trait::format::luminance ret; };
  template <>
  struct dim_to_dige_format<3> { typedef trait::format::rgb ret; };

  // Check if a milena's value type is a type from milena (i.e has enc
  // typedef) or a builtin type.
  template <typename T>
  struct mln_has_enc
  {
    template <typename V>
    static char a(V*, typename V::enc* = 0);
    static int a(...);
    enum { ret = sizeof(a((T*)0)) == sizeof(char) };
  };

  template <typename V, bool has_enc_typedef>
  struct mln_encoding_;

  template <typename V>
  struct mln_encoding_<V, true>
  {
    typedef typename V::enc ret;
  };

  template <typename V>
  struct mln_encoding_<V, false>
  {
    typedef V ret;
  };

  // Given a milena's value type V, get the encoding type of the
  // components of the value type.
  // Ex: rgb8 -> unsigned char, int_u16 -> short, rgbf -> float, char
  // -> char ...
  template <typename V>
  struct mln_comp_encoding
  {
    typedef typename mln_encoding_<mln_trait_value_comp(V, 0),
                                   mln_has_enc<mln_trait_value_comp(V, 0)>::ret >::ret
    ret;
  };


  // Dige adapter.
  template <typename V>
  image<typename dim_to_dige_format<mln::trait::value_<V>::dim>::ret, typename mln_comp_encoding<V>::ret >
  adapt(const mln::image2d<V>& i)
  {
    typedef image<typename dim_to_dige_format<mln::trait::value_<V>::dim>::ret, typename  mln_comp_encoding<V>::ret > ret;
    return ret(i.ncols() + i.border() * 2, i.nrows() + i.border() * 2, (const char*) i.buffer());
  }


}

#include <mln/io/ppm/load.hh>
#include <mln/io/pgm/load.hh>

int main()
{
  using namespace mln;
  using namespace dg;
  // avcodec_init();
  // avcodec_register_all();

  mln::trace::quiet = false;
  mln::trace::full_trace = true;
  //image2d<value::rgb8> lena = io::ppm::load<value::rgb8>("lena.ppm");
  image2d<value::int_u8> lena_pgm = io::pgm::load<value::int_u8>("lena.pgm");
  // image2d<value::int_u16> lena_pgm_u16(lena_pgm.domain());
  // image2d<float> lena_pgm_f(lena_pgm.domain());

  // std::map<int, test> map;
  // map[2] = test();

  // mln_piter_(image2d<value::int_u8>) p(lena_pgm.domain());
  // for_all(p)
  // {
  //   lena_pgm_f(p) = lena_pgm(p) / 255.;
  //   lena_pgm_u16(p) = lena_pgm(p) * 255;
  // }

  record("display.avi") <<= display("test", 200, 200)
    <<= dl() - lena_pgm;

  record("display.avi") <<= display("test", 200, 200)
    <<= dl() - lena_pgm;

  // display("hohoho", 200, 200) <<= dl() - lena_pgm;
  // display("fenetre 2", 400, 400) <<= dl() - lena;

  //  dg::pause();

  // display("test") <<= dl() - lena_pgm - lena +
  //   lena_pgm_f - lena_pgm_u16 - lena_pgm_u16;
  //  dg::pause();

  //  delete &record("display.avi");
  //  recorder::recorders().clear();
}
