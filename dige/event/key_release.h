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
**\file   key_release.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 16:04:24 2010
**
**\brief  key release.
**
**
*/

#ifndef DIGE_KEY_RELEASE_H_
# define DIGE_KEY_RELEASE_H_

# include <dige/event/event.h>
# include <dige/event/keycode.h>

class QObject;
class QEvent;

namespace dg
{

  namespace event
  {

    class key_release : public Event<key_release>
    {
    public:
      key_release();
      key_release(keycode k);

      bool operator==(const key_release& b) const;

    private:
      keycode k_;
    };

    any_event make_key_release_event(QObject *obj, QEvent *event);

  } // end of namespace event.

} // end of namespace dg.

#endif
