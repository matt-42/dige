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
**\file   displaylist.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Sep 25 10:00:59 2010
**
**\brief  displaylist implemetation
**
**
*/

#include <iostream>
#include <cmath>
#include <dige/displaylist.h>

namespace dg
{
  void free_textures(std::vector<std::vector<abstract_texture*> >* textures_)
  {
    for (unsigned i = 0; i < textures_->size(); i++)
      for (unsigned j = 0; j < (*textures_)[i].size(); j++)
      {
        (*textures_)[i][j]->unload();
        delete (*textures_)[i][j];
      }
    delete textures_;
  }

  displaylist::displaylist()
    : textures_(new std::vector<std::vector<abstract_texture*> >(1), free_textures),
      is_loaded_(false)
  {
  }

  displaylist::~displaylist()
  {
  }

  void
  displaylist::load()
  {
    for (unsigned i = 0; i < textures_->size(); i++)
      for (unsigned j = 0; j < (*textures_)[i].size(); j++)
        (*textures_)[i][j]->load();
    is_loaded_ = true;
  }

  void
  displaylist::clear()
  {
    assert(!is_loaded_);
    textures_->clear();
  }

  void
  displaylist::newline()
  {
    textures_->push_back(std::vector<abstract_texture*>());
  }

  void
  displaylist::unload()
  {
    for (unsigned i = 0; i < textures_->size(); i++)
      for (unsigned j = 0; j < (*textures_)[i].size(); j++)
        (*textures_)[i][j]->unload();
    is_loaded_ = false;
  }

  point2d<int>
  displaylist::dlist_to_image_coord(const layout& l, const point2d<float>& p)
  {
    for (unsigned i = 0; i < l.size(); i++)
    {
      for (unsigned j = 0; j < l[i].size(); j++)
      {
        if (l[i][j].has(p))
        {
          return point2d<int>(int((p[0] - l[i][j].origin()[0]) *
                                  (*textures_)[i][j]->width() / float(l[i][j].width())),
                              int((*textures_)[i][j]->height() - 1
                              -
                              std::floor((p[1] - l[i][j].origin()[1]) *
                                         (*textures_)[i][j]->height() / float(l[i][j].height()))));
        }
      }
    }
    return point2d<int>(-1, -1);
  }

  void
  displaylist::draw(unsigned width, unsigned height, layout& layout)
  {
    draw_(width, height, &layout);
  }

  void
  displaylist::draw(unsigned width, unsigned height)
  {
    draw_(width, height);
  }

  void
  displaylist::draw_(unsigned width, unsigned height, layout* layout)
  {
    glClear(GL_COLOR_BUFFER_BIT);

    if (layout)
      layout->clear();
    unsigned nrows = textures_->size();
    float rowheight = 1.f / nrows;
    for (unsigned i = 0; i < textures_->size(); i++)
    {
      if (layout)
        layout->push_back(std::vector<rect2d>());
      unsigned i_ = textures_->size() - i - 1;
      unsigned ncols = (*textures_)[i].size();
      float colwidth = 1.f / ncols;
      for (unsigned j = 0; j < (*textures_)[i].size(); j++)
      {
        float cell_width = width * colwidth;
        float cell_height = height * rowheight;
        float texture_ratio = float((*textures_)[i][j]->width()) / (*textures_)[i][j]->height();
        float cell_ratio = cell_width / cell_height;
        float l = j * colwidth;
        float r = (j+1) * colwidth;
        float b = i_ * rowheight;
        float t = (i_+1) * rowheight;

        if (texture_ratio < cell_ratio)
        {
          float tmp_l = (l+r)/2.f - (r-l)*texture_ratio/(2.*cell_ratio);
          r = (l+r)/2.f + (r-l)*texture_ratio/(2.*cell_ratio);
          l = tmp_l;
        }
        else
        {
          float tmp_b = (b+t)/2.f - (t-b)*cell_ratio/(2.*texture_ratio);
          t = (b+t)/2.f + (t-b)*cell_ratio/(2.*texture_ratio);
          b = tmp_b;
        }

        if (layout)
        {
          rect2d rect(point2d<float>(l * width, b * height),
                      (r - l) * width, (t - b) * height);
          (*layout)[i].push_back(rect);
        }

        glColor3f(0,1,0);
        glBindTexture(GL_TEXTURE_2D, (*textures_)[i][j]->gl_id());
        glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(l, b);
        glTexCoord2f(0,0); glVertex2f(l, t);
        glTexCoord2f(1,0); glVertex2f(r, t);
        glTexCoord2f(1,1); glVertex2f(r, b);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
      }
    }
  }

} // end of namespace dg.
