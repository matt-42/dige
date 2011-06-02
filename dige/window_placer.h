// Copyright (C) 2010, 2011 Matthieu Garrigues
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
**\file   window_placer.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 11 22:37:43 2010
**
**\brief  window_placer header.
**
**
*/

#ifndef DIGE_WINDOW_PLACER_H_
# define DIGE_WINDOW_PLACER_H_

# include <QDesktopWidget>
# include <QRect>

namespace dg
{
  /*!
  ** Randomly place windows on the screen. To minimize window
  ** overlapping.
  **
  */
  class window_placer
  {
  public:
    /*!
    ** Place a window of \p with * \p height.
    **
    ** \param width width
    ** \param height height
    **
    ** \return the position of the window on the screen
    */
    static inline QRect place(unsigned width, unsigned height)
    {
      if (screen_.width() == 0)
      {
        screen_ = QApplication::desktop()->availableGeometry();
      }

      return QRect(rand() % (screen_.width() - width),
                   rand() % (screen_.height() - height),
                   width, height);
    }

  private:
    static QRect screen_;         /*!< Dimensions of the current screen. */
  };

} // end of namespace dg.

#endif
