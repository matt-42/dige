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

#ifndef IMAGE_H_
# define IMAGE_H_

#include <dige/texture.hpp>

namespace dg
{

  template <typename F, typename C>
  class image
  {
  public:
    typedef image<F, C> self;
    //typedef make_vtype<F, C>::ret value_type;
    typedef char value_type;

    image();
    image(unsigned width, unsigned height,
          const char* buffer);

    image(const image& i);
    self& operator=(const image& i);

    unsigned width() const;
    unsigned height() const;
    const value_type* buffer() const;

  private:
    unsigned width_;
    unsigned height_;
    const value_type* buffer_;
  };

  template <typename F, typename C, unsigned S>
  texture adapt(const image<F, C>& i);

} // end of namespace dg.

# include <dige/image.hpp>

#endif
