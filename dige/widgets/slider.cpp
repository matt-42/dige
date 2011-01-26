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


namespace dg
{

  slider::slider(const std::string&, slider::orientation o)
  {
    if (o == slider::horizontal)
      slider_ = new QSlider(Qt::Horizontal);
    else
      slider_ = new QSlider(Qt::Vertical);
  }

  void slider::set_min_max(int min, int max)
  {
    slider_->setMinimum(min);
    slider_->setMaximum(max);
  }

  int
  slider::value() const
  {
    return slider_->value();
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

  slider& Slider(const std::string& title, slider::orientation o)
  {
    return named_instance<slider>(title, o);
  }

} // end of namespace dg.

