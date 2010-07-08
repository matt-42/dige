
#include <dige/window.h>
#include <dige/image.h>
#include <dige/value_traits.h>

#include <mln/core/image/image2d.hh>
#include <mln/value/rgb8.hh>
#include <mln/value/int_u16.hh>
#include <mln/value/rgb16.hh>
#include <mln/trait/value/comp.hh>
#include <mln/io/ppm/load.hh>
#include <mln/io/pgm/load.hh>
#include <mln/data/paste.hh>

namespace dg
{
  template <unsigned dim>
  struct mln_to_dige_format {};
  template <>
  struct mln_to_dige_format<1> { typedef trait::format::luminance ret; };
  template <>
  struct mln_to_dige_format<3> { typedef trait::format::rgb ret; };

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

  template <typename V>
  struct mln_comp_encoding
  {
    typedef typename mln_encoding_<mln_trait_value_comp(V, 0), mln_has_enc<mln_trait_value_comp(V, 0)>::ret >::ret ret;
  };


  template <typename V>
  image<typename mln_to_dige_format<mln::trait::value_<V>::dim>::ret, typename mln_comp_encoding<V>::ret >
  adapt(const mln::image2d<V>& i)
  {
    typedef image<typename mln_to_dige_format<mln::trait::value_<V>::dim>::ret, typename  mln_comp_encoding<V>::ret > ret;
    return ret(i.ncols() + i.border() * 2, i.nrows() + i.border() * 2, (const char*) i.buffer());
  }


}

int main()
{
  using namespace mln;
  using namespace dg;

  image2d<value::rgb8> lena = io::ppm::load<value::rgb8>("lena.ppm");
  //  image2d<value::rgb16> lena = io::ppm::load<value::rgb8>("lena.ppm");
  image2d<value::int_u8> lena_pgm = io::pgm::load<value::int_u8>("lena.pgm");
  image2d<value::int_u16> lena_pgm_u16(lena_pgm.domain());
  image2d<float> lena_pgm_f(lena_pgm.domain());

  //  mln::data::paste(lena_pgm, lena_pgm_u16);


  mln_piter_(image2d<value::int_u8>) p(lena_pgm.domain());
  for_all(p)
  {
    lena_pgm_f(p) = lena_pgm(p) / 255.;
    lena_pgm_u16(p) = lena_pgm(p) * 255;
  }


  display() <<= dl() - lena_pgm;// - lena - lena_pgm_f - lena_pgm_u16;
  // display(400, 400) <<= dl() -
  //   lena_pgm_f - lena_pgm - lena
  //   + lena - lena;

  dg::pause();

}
