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

#ifndef VALUE_TRAITS_H_
# define VALUE_TRAITS_H_

namespace dg
{
  namespace trait
  {

    namespace format
    {
      struct rgb { enum {to_gl_format = GL_RGB }; };
      struct luminance { enum {to_gl_format = GL_LUMINANCE }; };
    }

    template <typename C>
    struct gl_component_type {};

    template <>
    struct gl_component_type<float> { enum { ret = GL_FLOAT }; };

    template <>
    struct gl_component_type<char> { enum { ret = GL_BYTE }; };
    template <>
    struct gl_component_type<short> { enum { ret = GL_SHORT }; };
    template <>
    struct gl_component_type<int> { enum { ret = GL_INT }; };

    template <>
    struct gl_component_type<unsigned char> { enum { ret = GL_UNSIGNED_BYTE }; };
    template <>
    struct gl_component_type<unsigned short> { enum { ret = GL_UNSIGNED_SHORT }; };
    template <>
    struct gl_component_type<unsigned int> { enum { ret = GL_UNSIGNED_INT }; };

  }; // end of namespace trait.


} // end of namespace dg.

#endif
