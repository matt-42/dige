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
**\file   tracer_accu.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Dec 23 20:38:28 2010
**
**\brief  tracer_accu header
**
**
*/

#ifndef DIGE_TRACER_ACCU_H_
# define DIGE_TRACER_ACCU_H_

# include <map>
# include <string>
# include <ctime>
# include <boost/shared_ptr.hpp>
# include <dige/process_events.h>
# include <dige/point2d.h>

// Forward declaration.
class QPainterPath;
class QGraphicsPathItem;

namespace dg
{

  namespace widgets
  {

    /*!
    ** The tracer_accu hold and trace in tracer_view history of one
    ** traced value.
    */
    class tracer_accu
    {
    public:
      /*!
      ** Constructor.
      ** Initialize a new tracer_accu.
      **
      ** \param title The title of the tracer_accu
      **
      */
      tracer_accu();

      /// Destructor.
      ~tracer_accu();

      template <typename T>
        tracer_accu& operator<<(const T& elt)
      {
        double t = clock() / double(CLOCKS_PER_SEC);
        line_to(t, double(elt));
        //process_events();
        return *this;
      }

      template <typename T>
        tracer_accu& operator<<(const point2d<T>& p)
      {
        line_to(p[0], p[1]);
        //process_events();
        return *this;
      }

      QGraphicsPathItem* graphic_item();

      QPainterPath* painter();

      std::pair<float, float>
        minmax_since(float t) const;


    private:
      void line_to(double x, double y);

      boost::shared_ptr<QPainterPath> painter_;
      boost::shared_ptr<QGraphicsPathItem> item_;
    };

  } // end of namespace widgets.

} // end of namespace dg.

#endif
