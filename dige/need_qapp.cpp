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
**\file   need_qapp.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Dec 19 18:55:57 2010
**
**\brief  need_qapp implementation.
**
**
*/

#include <QApplication>

namespace dg
{

  void need_qapp()
  {
    if (!qApp)
    {
      static const char* dumy_argv = "";
      static int dumy_argc = 1;
      // Instanciate the main application object.
      new QApplication(dumy_argc, (char**)&dumy_argv);
    }

  }

} // end of namespace dg.
