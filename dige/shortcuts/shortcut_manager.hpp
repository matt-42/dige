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
**\file   shortcut_manager.hpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 24 22:37:43 2010
**
**\brief  shortcut_manager implementation.
**
**
*/

#ifndef DIGE_SHORTCUT_MANAGER_HPP_
# define DIGE_SHORTCUT_MANAGER_HPP_

# include <QObject>
# include <QApplication>

# include <dige/shortcuts/shortcut_manager.h>

namespace dg
{

  shortcut_manager::shortcut_manager()
  {
  }

  bool
  shortcut_manager::eventFilter(QObject* obj, QEvent* e)
  {
    if (e->type() == QEvent::KeyRelease)
    {
      int key = ((QKeyEvent*)e)->key();
      for (unsigned i = 0; shortcuts[i].key; i++)
        if (shortcuts[i].key == key)
          shortcuts[i].trigger(obj, e);
      return true;
    }
    else
    {
      return QObject::eventFilter(obj, e);
    }
  }

} // end of namespace dg.

#endif
