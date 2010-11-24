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
**\file   mouse_move.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 13:44:07 2010
**
**\brief  mouse_move header.
**
**
*/

#ifndef DIGE_MOUSE_MOVE_H_
# define DIGE_MOUSE_MOVE_H_

# include <dige/event/event.h>

class QObject;
class QEvent;

namespace dg
{

  class mouse_move : public Event<mouse_move>
  {
  public:
    mouse_move();
    mouse_move(QObject* widget);

    bool operator==(const mouse_move& b) const;

  private:
    QObject* widget_;
  };

  any_event make_mouse_move(QObject *obj, QEvent *event);

} // end of namespace dg.

#endif
