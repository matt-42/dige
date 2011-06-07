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
**\file   label.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Mon May 30 22:12:22 2011
**
**\brief  label header
**
**
*/

#ifndef DIGE_LABEL_H_
# define DIGE_LABEL_H_

# include <dige/widgets/widget.h>

// Forward declaration.
class QWidget;
class QLabel;

namespace dg
{

  namespace widgets
  {

    class label : public Widget<label>
    {
    public:

      /*!
      ** Constructor.
      ** Initialize a new label.
      **
      ** \param title The title of the label
      */
      label(const std::string& title);

      label& set_text(const std::string& s);

      /// Destructor.
      ~label();

      QWidget* widget() const;

    private:
      QLabel* label_;
    };

    /*!
    ** label factory. Retrieve the label named \p title. Create it if
    ** it doesn't exists.
    **
    ** \return the label.
    */
    label& Label(const std::string& title);

  } // end of namespace widgets.

} // end of namespace dg.

#endif
