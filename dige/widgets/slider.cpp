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
**\file   slider.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Wed Jan 26 21:55:12 2011
**
**\brief  slider implementation
**
**
*/

# include <string>

# include <QSlider>

# include <dige/named_object.h>
# include <dige/widgets/slider.h>
# include <dige/event/custom_events.h>

namespace dg
{

  namespace widgets
  {

    slider::slider(const std::string&, slider::orientation o)
    {
      if (o == slider::horizontal)
        slider_ = new slider_impl(Qt::Horizontal);
      else
        slider_ = new slider_impl(Qt::Vertical);
    }


    slider::slider(const std::string&,
                   int min, int max, int value,
                   slider::orientation o)
    {
      if (o == slider::horizontal)
        slider_ = new slider_impl(Qt::Horizontal);
      else
        slider_ = new slider_impl(Qt::Vertical);

      set_min_max(min, max);
      set_value(value);
    }

    void slider::set_min_max(int min, int max)
    {
      slider_->setMinimum(min);
      slider_->setMaximum(max);
      slider_->setTickInterval((max-min)/10);
      slider_->setTickPosition(QSlider::TicksAbove);
      slider_->setSingleStep(1);
    }

    int
    slider::value() const
    {
      return slider_->value();
    }

    void
    slider::set_value(int value)
    {
      slider_->setValue(value);
    }

    slider::~slider()
    {
      delete slider_;
    }

    QWidget*
    slider::widget()
    {
      return slider_;
    }

    event::any_event
    slider::changed_event() const
    {
      return event::slider_changed_event(slider_);
    }

    slider& Slider(const std::string& title, slider::orientation o)
    {
      return named_instance<slider>(title, o);
    }

    slider& Slider(const std::string& title,
                   int min, int max, int value, slider::orientation o)
    {
      return named_instance<slider>(title, min, max, value, o);
    }

  } // end of namespace widgets.

  namespace event
  {

    slider_changed_event::slider_changed_event(QObject* s)
      : slider_(s)
    {
      std::cout << s << std::endl;
    }

    bool
    slider_changed_event::operator==(const slider_changed_event& e)
    {
      return !slider_ || e.slider_ == slider_;
    }

    any_event make_slider_changed_event(QObject *obj, QEvent *event)
    {

      if (event->type() == static_cast<QEvent::Type>(slider_changed))
      {
        return slider_changed_event(obj);
      }
      else
        return any_event();
    }

  } // end of namespace event.

} // end of namespace dg.

