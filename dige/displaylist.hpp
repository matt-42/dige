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

#ifndef DISPLAYLIST_HPP_
# define DISPLAYLIST_HPP_

# include <dige/internal_texture.h>

namespace dg
{

  template <typename T>
  displaylist& displaylist::operator-(const T& i)
  {
    textures_->back().push_back(adapt_rec(i));
    return *this;
  }

  template <typename T>
  displaylist& displaylist::operator+(const T& i)
  {
    textures_->push_back(std::vector<abstract_texture*>());
    return *this - i;
  }

} // end of namespace dg.

#endif
