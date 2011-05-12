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
**\file   tracer.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Dec 23 20:30:09 2010
**
**\brief  Tracer header
**
**
*/

#ifndef DIGE_TRACER_H_
# define DIGE_TRACER_H_

# include <map>
# include <string>

# include <dige/widgets/tracer_accu.h>

// Forward declaration.
class QGraphicsScene;
class tracer_view;

namespace dg
{

  namespace widgets
  {

    /*!
    ** The tracer class allow to display the content of a displaylist
    ** in an OpenGL context.
    ** It listen to the tracer event (exposure, resizing...).
    */
    class tracer
    {
    public:
      /*!
      ** Constructor.
      ** Initialize a new tracer.
      **
      ** \param title The title of the tracer
      ** \param width width in pixels.
      ** \param height height in pixels.
      **
      */
      tracer(const std::string& title);

      /// Destructor.
      ~tracer();

      void set_dtime(float t);

      tracer_accu&
        operator[](const std::string& id);

      QWidget* widget();

    private:
      std::pair<float, float> minmax_since(float t);

      QGraphicsScene* scene_;
      tracer_view* view_;

      std::map<std::string, tracer_accu> accus_;
    };

    /*!
    ** tracer factory. Retrieve the tracer named \p title. Create it if
    ** it doesn't exists.
    **
    ** \param width tracer width in pixel.
    ** \param height tracer height in pixel.
    **
    ** \return the tracer.
    */
    tracer& Tracer(const std::string& title);

  } // end of namespace widgets.

} // end of namespace dg.

#endif
