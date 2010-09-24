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
**\file   reset_panzoom.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 24 22:37:43 2010
**
**\brief  reset_panzoom header.
**
**
*/

#ifndef DIGE_RESET_PANZOOM_H_
# define DIGE_RESET_PANZOOM_H_

# include <QApplication>
# include <QWidget>

namespace dg
{
  /*!
  ** Reset panzoom of \p obj if it is a gl_widget..
  **
  ** \param obj a QObject.
  */
  void reset_panzoom(QObject* obj, QEvent*);

} // end of namespace dg.

#endif

