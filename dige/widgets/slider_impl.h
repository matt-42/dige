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
**\file   slider_impl.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Feb 28 15:39:10 2011
**
**\brief  slider_impl header
**
**
*/

#ifndef DIGE_SLIDER_IMPL_H_
# define DIGE_SLIDER_IMPL_H_

# include <QSlider>

// Forward declaration.
class QWidget;
class QSlider;

namespace dg
{

  namespace widgets
  {

    class slider_impl : public QSlider
    {
    public:
      slider_impl(Qt::Orientation orientation, QWidget* parent = 0);
      void sliderChange(SliderChange change);
    };

  } // end of namespace widgets.

} // end of namespace dg.

#endif
