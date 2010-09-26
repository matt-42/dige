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
**\file   color_picker.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  color_picker header.
**
**
*/

#ifndef DIGE_COLOR_PICKER_H_
# define DIGE_COLOR_PICKER_H_

# include <QObject>
# include <QApplication>

# include <dige/singleton.h>
# include <dige/gl_widget.h>
# include <dige/color_picker_control.h>

namespace dg
{

  /*!
  ** Color_Picker.
  */
  class color_picker : public QObject, public singleton<color_picker>
  {
  private:
    /// Constructor.
    color_picker();

  public:
    friend class singleton<color_picker>;

    /*!
    ** Filter color_picker events.
    **
    ** \param obj watched object.
    ** \param e event
    **
    ** \return true if the event has been catched.
    */
    bool eventFilter(QObject *obj, QEvent *event);
  };

} // end of namespace dg.

#endif

