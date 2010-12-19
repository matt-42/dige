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
**\file   error.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Tue Oct 19 23:06:52 2010
**
**\brief  OpenGL error handler.
**
**
*/

#ifndef DIGE_ERROR
# define DIGE_ERROR

# include <iostream>
# include <GL/glu.h>

namespace dg
{

#define check_gl_error() \
  {\
    GLenum err = glGetError();\
    if (err != GL_NO_ERROR)\
    {\
      std::cerr << "Opengl Error at" << __FILE__ << "(" << __LINE__ << "): "  << std::endl;\
      assert(0);\
    }\
  }
}

#endif
