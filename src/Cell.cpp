//
//  Copyright (C) 2004-2014 Andrej Vodopivec <andrej.vodopivec@gmail.com>
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
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "Cell.h"

Cell::Cell()
{
  m_nextToDraw = NULL;
  m_previousToDraw = NULL;
  m_group = NULL;
  m_maxCenter = -1;
  m_maxDrop = -1;
  m_width = -1;
  m_height = -1;
  m_center = -1;
  m_breakLine = false;
  m_breakPage = false;
  m_forceBreakLine = false;
  m_bigSkip = true;
  m_isHidden = false;
  m_isBroken = false;
  m_highlight = false;
  m_type = MC_TYPE_DEFAULT;
  m_textStyle = TS_VARIABLE;
}

Cell::~Cell()
{}

void Cell::SetType(int type)
{
	m_type = type;

	switch (m_type)
	{
		case MC_TYPE_MAIN_PROMPT:
			m_textStyle = TS_MAIN_PROMPT;
			break;
		case MC_TYPE_PROMPT:
			m_textStyle = TS_OTHER_PROMPT;
			break;
		case MC_TYPE_LABEL:
			m_textStyle = TS_LABEL;
			break;
		case MC_TYPE_INPUT:
			m_textStyle = TS_INPUT;
			break;
		case MC_TYPE_ERROR:
			m_textStyle = TS_ERROR;
			break;
		case MC_TYPE_TEXT:
			m_textStyle = TS_TEXT;
			break;
		case MC_TYPE_SUBSECTION:
			m_textStyle = TS_SUBSECTION;
			break;
		case MC_TYPE_SECTION:
			m_textStyle = TS_SECTION;
			break;
		case MC_TYPE_TITLE:
			m_textStyle = TS_TITLE;
			break;
		default:
			m_textStyle = TS_DEFAULT;
	}

}


/***
 * Get the pointer to the parent group cell
 */

Cell* Cell::GetParent()
{
  return m_group;
}

void Cell::RecalculateWidths(CellParser& parser, int fontsize)
{
  ResetData();
}

/*! Is this cell currently visible in the window?.
 */
bool Cell::DrawThisCell(CellParser& parser, wxPoint point)
{
  int top = parser.GetTop();
  int bottom = parser.GetBottom();
  if (top == -1 || bottom == -1)
    return true;
  if (point.y - GetMaxCenter() > bottom || point.y + GetMaxDrop() < top)
    return false;
  return true;
}

wxRect Cell::GetRect()
{
  if (m_isBroken)
    return wxRect( -1, -1, 0, 0);
  else
    return wxRect(m_currentPoint.x, m_currentPoint.y - m_center,
                m_width, m_height);
}

void Cell::DrawBoundingBox(wxDC& dc, int border)
{
  wxRect rect = GetRect();
  int x = rect.GetX(), y = rect.GetY();
  int width = rect.GetWidth(), height = rect.GetHeight();
  dc.DrawRectangle(x - border, y - border, width + 2*border, height + 2*border);
}

/***
 * Is operator - draw () in frac...
 */
bool Cell::IsOperator()
{
  return false;
}

/***
 * Get the part for diff tag support - only ExpTag overvrides this.
 */
wxString Cell::GetDiffPart()
{
  return wxEmptyString;
}

/***
 * Find the first and last cell in rectangle rect in this line.
 */
void Cell::SelectRect(wxRect& rect, Cell** first, Cell** last)
{
  SelectFirst(rect, first);
  if (*first != NULL)
  {
    *last = *first;
    (*first)->SelectLast(rect, last);
    if (*last == *first)
      (*first)->SelectInner(rect, first, last);
  }
  else
    *last = NULL;
}

bool Cell::BreakLineHere()
{
  return (!m_isBroken && (m_breakLine || m_forceBreakLine));
}

bool Cell::ContainsRect(wxRect& sm)
{
  wxRect big = GetRect();
  if (big.x <= sm.x &&
          big.y <= sm.y &&
          big.x + big.width >= sm.x + sm.width &&
          big.y + big.height >= sm.y + sm.height)
    return true;
  return false;
}

/*!
 Resets remembered data.

 Resets cached data like width and the height of the current cell
 as well as the vertical position of the center. Temporarily unbreaks all
 lines until the widths are recalculated if there aren't any hard line 
 breaks.
 */
void Cell::ResetData()
{
  m_maxCenter = -1;
  m_maxDrop = -1;
//  m_currentPoint.x = -1;
//  m_currentPoint.y = -1;
  m_breakLine = m_forceBreakLine;
}

void Cell::SetParent(Cell *parent)
{
  m_group = parent;
}

/***
 * Set the pen in device context accordint to the style of the cell.
 */
void Cell::SetPen(CellParser& parser)
{
  wxDC& dc = parser.GetDC();
  if (m_highlight)
    dc.SetPen(*(wxThePenList->FindOrCreatePen(parser.GetColor(TS_HIGHLIGHT),
                1, wxPENSTYLE_SOLID)));
  else if (m_type == MC_TYPE_PROMPT)
    dc.SetPen(*(wxThePenList->FindOrCreatePen(parser.GetColor(TS_OTHER_PROMPT),
                1, wxPENSTYLE_SOLID)));
  else if (m_type == MC_TYPE_INPUT)
    dc.SetPen(*(wxThePenList->FindOrCreatePen(parser.GetColor(TS_INPUT),
                1, wxPENSTYLE_SOLID)));
  else
    dc.SetPen(*(wxThePenList->FindOrCreatePen(parser.GetColor(TS_DEFAULT),
                    1, wxPENSTYLE_SOLID)));
}

/***
 * Reset the pen in the device context.
 */
void Cell::UnsetPen(CellParser& parser)
{
  wxDC& dc = parser.GetDC();
  if (m_type == MC_TYPE_PROMPT || m_type == MC_TYPE_INPUT || m_highlight)
    dc.SetPen(*(wxThePenList->FindOrCreatePen(parser.GetColor(TS_DEFAULT),
                1, wxPENSTYLE_SOLID)));
}

/***
 * Copy all important data from s to t
 */
void Cell::CopyData(Cell* s, Cell* t)
{
  t->m_altCopyText = s->m_altCopyText;
  t->m_forceBreakLine = s->m_forceBreakLine;
  t->m_type = s->m_type;
  t->m_textStyle = s->m_textStyle;
}

void Cell::SetForeground(CellParser& parser)
{
  wxColour color;
  wxDC& dc = parser.GetDC();
  if (m_highlight)
  {
    color = parser.GetColor(TS_HIGHLIGHT);
  }
  else {
    switch (m_type)
    {
    case MC_TYPE_PROMPT:
      color = parser.GetColor(TS_OTHER_PROMPT);
      break;
    case MC_TYPE_MAIN_PROMPT:
      color = parser.GetColor(TS_MAIN_PROMPT);
      break;
    case MC_TYPE_ERROR:
      color = wxColour(wxT("red"));
      break;
    case MC_TYPE_LABEL:
      color = parser.GetColor(TS_LABEL);
      break;
    default:
      color = parser.GetColor(m_textStyle);
      break;
    }
  }

  dc.SetTextForeground(color);
}

bool Cell::IsMath()
{
  return !(m_textStyle == TS_DEFAULT ||
           m_textStyle == TS_LABEL ||
           m_textStyle == TS_INPUT);
}
