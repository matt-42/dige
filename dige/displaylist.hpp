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

#ifndef DISPLAYLIST_HPP_
# define DISPLAYLIST_HPP_

#include <iostream>

namespace dg
{
  displaylist::displaylist()
    : textures_(1)
  {
  }

  template <typename T>
  displaylist& displaylist::operator-(const T& i)
  {
    textures_.back().push_back(adapt_rec(i));
    return *this;
  }

  template <typename T>
  displaylist& displaylist::operator+(const T& i)
  {
    textures_.push_back(std::vector<texture>());
    return *this - i;
  }


  template <typename T>
  texture displaylist::adapt_rec(const T& i)
  {
    return adapt_rec(adapt(i));
  }

  texture displaylist::adapt_rec(texture i)
  {
    return i;
  }

  void
  displaylist::draw(unsigned width, unsigned height)
  {
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned nrows = textures_.size();
    float rowsize = 1. / nrows;
    for (unsigned i = 0; i < textures_.size(); i++)
    {
      unsigned i_ = textures_.size() - i - 1;
      unsigned ncols = textures_[i].size();
      float colsize = 1. / ncols;
      for (unsigned j = 0; j < textures_[i].size(); j++)
      {
        float cell_width = width * colsize;
        float cell_height = height * rowsize;
        float texture_ratio = float(textures_[i][j].width()) / textures_[i][j].height();
        float cell_ratio = cell_width / cell_height;
        float l = j * colsize;
        float r = (j+1) * colsize;
        float b = i_ * rowsize;
        float t = (i_+1) * rowsize;

        if (texture_ratio < cell_ratio)
        {
          l = (l+r)/2. - (r-l)*texture_ratio/(2.*cell_ratio);
          r = (l+r)/2. + (r-l)*texture_ratio/(2.*cell_ratio);
        }
        else
        {
          b = (b+t)/2. - (t-b)*cell_ratio/(2.*texture_ratio);
          t = (b+t)/2. + (t-b)*cell_ratio/(2.*texture_ratio);
        }

        textures_[i][j].load();
        glColor3f(0,1,0);
        glBindTexture(GL_TEXTURE_2D, textures_[i][j].gl_id());
        glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(l, b);
        glTexCoord2f(0,0); glVertex2f(l, t);
        glTexCoord2f(1,0); glVertex2f(r, t);
        glTexCoord2f(1,1); glVertex2f(r, b);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        textures_[i][j].unload();
      }
    }
  }

} // end of namespace dg.

#endif
