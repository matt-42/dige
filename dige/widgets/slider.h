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
**\file   slider.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Wed Jan 26 22:47:38 2011
**
**\brief  slider header
**
**
*/

#ifndef DIGE_SLIDER_H_
# define DIGE_SLIDER_H_

# include <map>
# include <string>

// Forward declaration.
class QWidget;
class QSlider;

namespace dg
{

  /*!
  ** The slider class allow to display the content of a displaylist
  ** in an OpenGL context.
  ** It listen to the slider event (exposure, resizing...).
  */
  class slider
  {
  public:
    enum orientation { horizontal, vertical };

    /*!
    ** Constructor.
    ** Initialize a new slider.
    **
    ** \param title The title of the slider
    ** \param width width in pixels.
    ** \param height height in pixels.
    **
    */
    slider(const std::string& title, orientation o);

    void set_min_max(int min, int max);
    int value() const;

    /// Destructor.
    ~slider();

    QWidget* widget();

  private:
    QSlider* slider_;
  };

  /*!
  ** slider factory. Retrieve the slider named \p title. Create it if
  ** it doesn't exists.
  **
  ** \return the slider.
  */
  slider& Slider(const std::string& title,
                 slider::orientation o = slider::horizontal);

} // end of namespace dg.

#endif
