// Copyright (C) 2010,2011 Matthieu Garrigues
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
# include <dige/event/event.h>
# include <dige/widgets/widget.h>
# include <dige/widgets/slider_impl.h>

// Forward declaration.
class QWidget;
class QSlider;
class QBoxLayout;
class QLayout;

namespace dg
{

  namespace widgets
  {

    /*!
    ** The slider class allow to display the content of a displaylist
    ** in an OpenGL context.
    ** It listen to the slider event (exposure, resizing...).
    */
    class slider : public Widget<slider>
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
      slider(const std::string& title, int min, int max,
             int value, orientation o);

      void set_min_max(int min, int max);
      void set_value(int value);
      int value() const;

      /// Destructor.
      ~slider();

      QLayout* widget();

      event::any_event changed_event() const;

    private:
      void build_layout(const std::string& s, slider::orientation o);

      slider_impl* slider_;
      QBoxLayout* layout_;
    };

    /*!
    ** slider factory. Retrieve the slider named \p title. Create it if
    ** it doesn't exists.
    **
    ** \return the slider.
    */
    slider& Slider(const std::string& title,
                   slider::orientation o = slider::horizontal);

    slider& Slider(const std::string& title,
                   int min, int max, int value,
                   slider::orientation o = slider::horizontal);

  } // end of namespace widgets.

  namespace event
  {

    class slider_changed_event : public event::Event<slider_changed_event>
    {
    public:
      slider_changed_event(QObject* s);
      bool operator==(const slider_changed_event& e);

    private:
      QObject* slider_;
    };

    any_event make_slider_changed_event(QObject *obj, QEvent *event);

  } // end of namespace event.

} // end of namespace dg.

#endif
