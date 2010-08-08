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

#ifndef DISPLAYLIST_H_
# define DISPLAYLIST_H_

#include <dige/texture.h>

namespace dg
{

  class displaylist
  {
  public:
    inline displaylist();

    template <typename T>
    inline displaylist& operator-(const T& i);

    template <typename T>
    inline displaylist& operator+(const T& i);


    inline void load();
    inline void unload();
    inline void draw(unsigned width, unsigned height);

  private:
    template <typename T>
    inline texture adapt_rec(const T& i);

    inline texture adapt_rec(texture i);

    std::vector<std::vector<texture> > textures_;
  };

  typedef displaylist dl;

} // end of namespace dg.

# include <dige/displaylist.hpp>

#endif
