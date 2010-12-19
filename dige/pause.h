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
**\file   pause.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Dec 12 17:15:04 2010
**
**\brief  Pause header.
**
**
*/

#ifndef DIGE_PAUSE_H_
# define DIGE_PAUSE_H_

namespace dg
{

  /*!
  ** Pause the current thread until the user press the space key in any of the
  ** window. It need at least one created window.
  */
  void pause();

} // end of namespace dg.

#endif
