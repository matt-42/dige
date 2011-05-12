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
**\file   slider_impl.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Feb 28 15:43:35 2011
**
**\brief  slider_impl implementation.
**
**
*/

#include <QApplication>
#include <QEvent>
#include <QWidget>
#include <QSlider>

#include <dige/event/custom_events.h>
#include <dige/widgets/slider_impl.h>

namespace dg
{

  namespace widgets
  {

    slider_impl::slider_impl(Qt::Orientation orientation, QWidget* parent)
      : QSlider(orientation, parent)
    {
    }

    void slider_impl::sliderChange(SliderChange change)
    {
      QSlider::sliderChange(change);
      QEvent e(static_cast<QEvent::Type>(int(event::slider_changed)));
      QApplication::sendEvent(this, &e);
    }

  } // end of namespace widgets.

} // end of namespace dg.

