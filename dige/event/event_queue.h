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
**\file   event_queue.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Feb 26 19:35:43 2011
**
**\brief  event_queue header.
**
**
*/

#ifndef DIGE_EVENT_QUEUE_H_
# define DIGE_EVENT_QUEUE_H_

# include <queue>
# include <dige/event/event.h>
# include <dige/event/event_set.h>

class QObject;
class QEvent;

namespace dg
{

  namespace event
  {

    class event_queue : public QObject
    {
    public:
      event_queue(const any_event_set& e);
      event_queue(const any_event& e);
      ~event_queue();

      bool is_empty() const;
      unsigned size() const;
      any_event pop_front();
      void clear();
      bool eventFilter(QObject *obj, QEvent *event);

    private:
      std::queue<any_event> queue_;
      any_event_set s_;
    };

  } // end of namespace event.

} // end of namespace dg.

#endif
