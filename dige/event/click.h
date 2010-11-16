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
**\file   click.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 13:44:07 2010
**
**\brief  click header.
**
**
*/

#ifndef DIGE_CLICK_H_
# define DIGE_CLICK_H_

# include <dige/event/event.h>

class QObject;
class QEvent;

namespace dg
{

  class click : public Event<click>
  {
  public:
    click();
    click(QObject* widget);

    bool operator==(const click& b);

  private:
    QObject* widget_;
  };

  any_event make_click(QObject *obj, QEvent *event);

} // end of namespace dg.

#endif
