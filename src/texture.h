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

#ifndef TEXTURE_H_
# define TEXTURE_H_

#include <SFML/OpenGL.hpp>

namespace dg
{

  class texture
  {
  public:
    texture();
    texture(unsigned width, unsigned height,
            GLuint comp_type, GLuint format,
            GLuint filter,
            const char* buffer);

    texture(const texture&);
    texture& operator=(const texture&);

    ~texture();

    unsigned width() const;
    unsigned height() const;

    void load();
    void unload();

    GLuint gl_id() const;

  private:
    unsigned width_;
    unsigned height_;
    GLuint comp_type_;
    GLuint format_;
    GLuint filter_;
    const char* buffer_;
    GLuint gl_id_;
  };

} // end of namespace dg.

# include <dige/texture.hpp>

#endif
