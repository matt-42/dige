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
**\file   panzoom_control.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon Sep  6 22:15:37 2010
**
**\brief  panzoom_control header.
**
**
*/

#ifndef DIGE_PANZOOM_CONTROL_H_
# define DIGE_PANZOOM_CONTROL_H_

# include <QTextStream>
# include <QPainter>
# include <QWidget>

# include <GL/gl.h>

# include <dige/singleton.h>
# include <dige/gl_widget.h>

namespace dg
{

  /*!
  ** panzoom_control display information about a color.
  */
  class panzoom_control : public QGLWidget, public singleton<panzoom_control>
  {
  public:
    friend class singleton<panzoom_control>;

    /*!
    ** Place the panzoom_control window under the cursor.
    **
    ** \param e a mouse event.
    */
    void place(gl_widget* w);

    /*!
    ** Update control.
    **
    ** \param p a position.
    ** \param c a color.
    */
    void update(gl_widget* w);

    /*!
    ** Draw the window content.
    */
    //    void paintEvent(QPaintEvent *);

    /*!
    ** Hide the control.
    **
    */
    void hide();

    /// Move the window to the top.
    void activateWindow();

  protected:

    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();

  private:
    /*!
    ** Constructor. Build the window.
    */
    panzoom_control();

    gl_widget* widget_;              /*!< current gl_widget. */

    static const unsigned width_ = 200;
    static const unsigned height_ = 200;
  };

} // end of namespace dg.

#endif
