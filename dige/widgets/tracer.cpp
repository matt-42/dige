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
**\file   tracer.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Dec 23 20:29:54 2010
**
**\brief  Tracer implementation
**
**
*/

# include <map>
# include <string>

# include <QGraphicsScene>
# include <QGraphicsView>
# include <QLabel>
# include <QtDebug>
# include <QGLWidget>

# include <dige/widgets/tracer_accu.h>
# include <dige/widgets/tracer_view.h>
# include <dige/widgets/tracer.h>
# include <dige/named_object.h>
# include <dige/need_qapp.h>

namespace dg
{

  namespace widgets
  {

    tracer::tracer(const std::string&)
    {
      need_qapp();
      scene_ = new QGraphicsScene();
      view_ = new tracer_view(scene_);
      view_->set_view_dtime(5);
      view_->set_view_dy(1);
    }

    tracer::~tracer()
    {
      delete scene_;
      delete view_;
    }

    void
    tracer::set_dtime(float t)
    {
      view_->set_view_dtime(t);
    }

    std::pair<float, float>
    tracer::minmax_since(float t)
    {
      if (accus_.size())
      {
        std::map<std::string, tracer_accu>::const_iterator it = accus_.begin();
        std::pair<float, float> res = accus_.begin()->second.minmax_since(t);
        it++;
        for (;it != accus_.end();it++)
        {
          std::pair<float, float> tmp = it->second.minmax_since(t);
          if (res.first > tmp.first) res.first = tmp.first;
          if (res.second < tmp.second) res.second = tmp.second;
        }
        return res;
      }
      return std::pair<float, float>(0,1);
    }

    tracer_accu&
    tracer::operator[](const std::string& id)
    {
      static clock_t prev_update = clock();

      if (accus_.find(id) == accus_.end())
      {
        tracer_accu& a = accus_[id];
        scene_->addItem((QGraphicsItem*)a.graphic_item());
      }

      static float max_visible_t = 0.f;
      float t = clock() / float(CLOCKS_PER_SEC);

      if (t > max_visible_t)
        max_visible_t = t + view_->dt();

      if (clock() - prev_update > (CLOCKS_PER_SEC/100.))
      {
        prev_update = clock();
        std::pair<float, float> mm = minmax_since(max_visible_t - view_->dt());
        view_->set_view_dy(mm.second - mm.first);
        view_->update_scale();
        scene_->setSceneRect(max_visible_t - view_->dt(), mm.first,
                             view_->dt(), mm.second - mm.first);
        scene_->update();
        process_events();
      }

      return accus_[id];
    }

    QWidget*
    tracer::widget()
    {
      return view_;
    }

    tracer& Tracer(const std::string& title)
    {
      return named_instance<tracer>(title);
    }

  } // end of namespace widgets.

} // end of namespace dg.
