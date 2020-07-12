// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2009-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//  SPDX-License-Identifier: GPL-2.0+

/*! \file

  This file contains the definition of the class History that handles the recently 
  issued commands for the history pane.
 */

#ifndef HISTORY_H
#define HISTORY_H

#include "precomp.h"
#include "LoggingMessageDialog.h"
#include <wx/wx.h>
#include <wx/regex.h>

enum
{
  history_ctrl_id = 1,
  history_regex_id,
  export_all,
  export_session,
  export_visible,
  export_selected
};

/*! This class generates a pane containing the last commands that were issued.

 */
class History : public wxPanel
{
public:
  History(wxWindow *parent, int id);

  /* The destructor

   */
  ~History();

  //! Add a file to the recently opened files list.
  void AddToHistory(const wxString &cmd);

  void OnRegExEvent(wxCommandEvent &ev);

  void UpdateDisplay();

  wxString GetCommand(bool next);

  void MaximaSessionStart();
  
protected:
  //! Called on right-clicks on the history panel
  void OnMouseRightDown(wxMouseEvent &event);
  void OnMenu(wxCommandEvent &event);
private:
  int m_sessionCommands = 0;
  wxListBox *m_history;
  wxTextCtrl *m_regex;
  wxArrayString m_commands;
  //! The currently selected item. -1=none.
  long m_current;
  //! The tooltip that is displayed if the regex cannot be interpreted
  static wxString m_regexTooltip_error;
  //! The tooltip that is displayed if the regex is empty or can be interpreted
  static wxString m_regexTooltip_norm;
  //! The regex entries need to be matched to in order to be displayed
  wxRegEx m_matcher;

};

#endif // HISTORY_H
