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
/*!
**\file   dsl.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Dec  4 10:37:07 2010
**
**\brief  Dige's domain specific language elements.
**
**
*/

#ifndef DIGE_DSL_H_
# define DIGE_DSL_H_

namespace dg
{


  // enum vbox_start_ { vbox_start };
  // enum vbox_end_   { vbox_end };

  // enum hbox_start_ { hbox_start };
  // enum hbox_end_   { hbox_end };

  template <typename T>
  struct Literal {};


  struct vbox_start_ {};
  struct vbox_end_   {};
  struct hbox_start_ {};
  struct hbox_end_   {};

  static const Literal<vbox_start_> vbox_start = {};
  static const Literal<vbox_end_>   vbox_end   = {};
  static const Literal<hbox_start_> hbox_start = {};
  static const Literal<hbox_end_>   hbox_end   = {};

} // end of namespace dg.

#endif
