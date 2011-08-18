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
**\file   label.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon May 30 22:14:44 2011
**
**\brief  label sources
**
**
*/

# include <string>
# include <QLabel>
# include <QString>
# include <QSizePolicy>

# include <dige/need_qapp.h>
# include <dige/named_object.h>
# include <dige/widgets/label.h>

namespace dg
{

  namespace widgets
  {

    label::label(const std::string& s)
    {
      need_qapp();
      label_ = new QLabel();
      set_text(s);
      label_->adjustSize();
      label_->setGeometry(0,0, 200, 30);
      label_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    label&
    label::set_text(const std::string& s)
    {
      label_->setText(QString::fromStdString(s));
      label_->adjustSize();
      label_->setGeometry(0,0, 200, 30);
      label_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
      return *this;
    }

    label::~label()
    {
    }

    QWidget*
    label::widget() const
    {
      return label_;
    }

    label& Label(const std::string& title)
    {
      return named_instance<label>(title);
    }

  } // end of namespace widgets.

} // end of namespace dg.
