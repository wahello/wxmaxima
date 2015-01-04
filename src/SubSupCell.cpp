//
//  Copyright (C) 2007-2014 Andrej Vodopivec <andrej.vodopivec@gmail.com>
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

#include "SubSupCell.h"

#define SUBSUP_DEC 3

SubSupCell::SubSupCell() : Cell()
{
  m_baseCell = NULL;
  m_indexCell = NULL;
  m_exptCell = NULL;
}
SubSupCell::~SubSupCell()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_indexCell != NULL)
    delete m_indexCell;
  if (m_exptCell != NULL)
    delete m_exptCell;
}

void SubSupCell::SetParent(Cell *parent)
{
  if (m_baseCell != NULL)
    m_baseCell->SetParent(parent);
  if (m_indexCell != NULL)
    m_indexCell->SetParent(parent);
  if (m_exptCell != NULL)
    m_exptCell->SetParent(parent);

  Cell::SetParent(parent);
}

Cell* SubSupCell::Copy()
{
  SubSupCell* tmp = new SubSupCell;
  CopyData(this, tmp);
  tmp->SetBase(m_baseCell->Copy());
  tmp->SetIndex(m_indexCell->Copy());
  tmp->SetExponent(m_exptCell->Copy());

  return tmp;
}

void SubSupCell::Destroy()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_indexCell != NULL)
    delete m_indexCell;
  if (m_exptCell != NULL)
    delete m_exptCell;
  m_baseCell = NULL;
  m_indexCell = NULL;
  m_exptCell = NULL;
}

void SubSupCell::SetIndex(CellList *index)
{
  if (index == NULL)
    return ;
  if (m_indexCell != NULL)
    delete m_indexCell;
  m_indexCell = index;
}

void SubSupCell::SetBase(CellList *base)
{
  if (base == NULL)
    return ;
  if (m_baseCell != NULL)
    delete m_baseCell;
  m_baseCell = base;
}

void SubSupCell::SetExponent(CellList *exp)
{
  if (exp == NULL)
    return ;
  if (m_exptCell != NULL)
    delete m_exptCell;
  m_exptCell = exp;
}

void SubSupCell::RecalculateWidths(CellParser& parser, int fontsize)
{
  double scale = parser.GetScale();
  m_baseCell->RecalculateWidths(parser, fontsize);
  m_indexCell->RecalculateWidths(parser, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));
  m_exptCell->RecalculateWidths(parser, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));
  m_width = m_baseCell->GetFullWidth(scale) +
            MAX(m_indexCell->GetFullWidth(scale), m_exptCell->GetFullWidth(scale)) -
            SCALE_PX(2, parser.GetScale());
  Cell::RecalculateWidths(parser, fontsize);
}

void SubSupCell::RecalculateSize(CellParser& parser, int fontsize)
{
  double scale = parser.GetScale();

  m_baseCell->RecalculateSize(parser, fontsize);
  m_indexCell->RecalculateSize(parser, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));
  m_exptCell->RecalculateSize(parser, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));

  m_height = m_baseCell->GetMaxHeight() + m_indexCell->GetMaxHeight() +
             m_exptCell->GetMaxHeight() -
             2*SCALE_PX((8 * fontsize) / 10 + MC_EXP_INDENT, parser.GetScale());

  m_center = m_exptCell->GetMaxHeight() + m_baseCell->GetMaxCenter() -
             SCALE_PX((8 * fontsize) / 10 + MC_EXP_INDENT, scale);

  Cell::RecalculateSize(parser, fontsize);
}

void SubSupCell::Draw(CellParser& parser, wxPoint point, int fontsize)
{
  if (DrawThisCell(parser, point))
  {
    double scale = parser.GetScale();
    wxPoint bs, in;

    bs.x = point.x;
    bs.y = point.y;
    m_baseCell->Draw(parser, bs, fontsize);

    in.x = point.x + m_baseCell->GetFullWidth(scale) - SCALE_PX(2, scale);
    in.y = point.y + m_baseCell->GetMaxDrop() +
           m_indexCell->GetMaxCenter() -
           SCALE_PX((8 * fontsize) / 10 + MC_EXP_INDENT, scale);
    m_indexCell->Draw(parser, in, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));

    in.y = point.y - m_baseCell->GetMaxCenter() - m_exptCell->GetMaxHeight()
           + m_exptCell->GetMaxCenter() +
           SCALE_PX((8 * fontsize) / 10 + MC_EXP_INDENT, scale);
    m_exptCell->Draw(parser, in, MAX(MC_MIN_SIZE, fontsize - SUBSUP_DEC));
  }

  Cell::Draw(parser, point, fontsize);
}

wxString SubSupCell::ToString()
{
  wxString s;
  if (m_baseCell->IsCompound())
    s += wxT("(") + m_baseCell->ToString() + wxT(")");
  else
    s += m_baseCell->ToString();
  s += wxT("[") + m_indexCell->ToString() + wxT("]");
  s += wxT("^");
  if (m_exptCell->IsCompound())
    s += wxT("(");
  s += m_exptCell->ToString();
  if (m_exptCell->IsCompound())
    s += wxT(")");
  return s;
}

wxString SubSupCell::ToTeX()
{
  wxString s = wxT("{") + m_baseCell->ToTeX() + wxT("}_{") +
               m_indexCell->ToTeX() + wxT("}^{") +
               m_exptCell->ToTeX() + wxT("}");
  return s;
}

wxString SubSupCell::ToXML()
{
  return _T("<ie><r>") + m_baseCell->ToXML()
    + _T("</r><r>") + m_indexCell->ToXML()
    + _T("</r><r>") + m_exptCell->ToXML()
    + _T("</r></ie>");
}

void SubSupCell::SelectInner(wxRect& rect, Cell **first, Cell **last)
{
  *first = NULL;
  *last = NULL;
  if (m_indexCell->ContainsRect(rect))
    m_indexCell->SelectRect(rect, first, last);
  else if (m_baseCell->ContainsRect(rect))
    m_baseCell->SelectRect(rect, first, last);
  else if (m_exptCell->ContainsRect(rect))
    m_exptCell->SelectRect(rect, first, last);
  if (*first == NULL || *last == NULL)
  {
    *first = this;
    *last = this;
  }
}
