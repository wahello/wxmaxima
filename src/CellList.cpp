#include "CellList.h"
CellList::CellList()
{
}


void CellList::AppendCell(Cell *p_next)
{
  // If there is nothing to append we return immediately.
  if (p_next == NULL) return ;

  // We want to app end something. Therefore the size information has to
  // be recalculated.
  ResetData();
  
  if(!empty())
    (*end())->m_nextToDraw=p_next;
  push_back(p_next);
};

int CellList::GetFullWidth(double scale)
{
  // Recalculate the width only if there is no cached value.
  if (m_fullWidth == -1)
    {
      m_fullWidth=0;
      for(iterator i=begin();i!=end();i++)
	{
	  m_fullWidth = (*i)->GetWidth();
	  if(i!=end())
	    m_fullWidth += SCALE_PX(MC_CELL_SKIP, scale);
	}
    }
  return m_fullWidth;
}

int CellList::GetMaxCenter()
{
  // -1 means we need to recalculate this value.
  if (m_maxCenter == -1)
  {
    Cell *tmp=front();

    do
      {
	if(m_maxCenter>tmp->GetCenter())
	  m_maxCenter=tmp->GetCenter();
	
	tmp=tmp->m_nextToDraw;
      } while ((tmp!=NULL)&&(!tmp->m_isBroken))
  }
  return m_maxCenter;
}

int CellList::GetMaxDrop()
{
  // -1 means we need to recalculate this value.
  if (m_maxCenter == -1)
  {
    Cell *tmp=front();

    do
      {
	if(m_maxDrop>tmp->GetDrop())
	  m_maxDrop= tmp->GetDrop();
	
	tmp=tmp->m_nextToDraw;
      } while ((tmp!=NULL)&&(!tmp->m_isBroken))
  }
  return m_maxCenter;
}

int CellList::GetMaxHeight()
{
  return GetMaxCenter() + GetMaxDrop();
}

/*! Get the width of this line.
 */
int CellList::GetLineWidth(double scale)
{
  if (m_lineWidth == -1)
  {
    int width;
    for(iterator i=begin();i!=end();i++)
      {
	if(
	   ((*i)->m_isBroken) ||
	   (i==begin())
	   )
	  width=(*i)->GetWidth();
	else
	  width+=(*i)->GetWidth()+SCALE_PX(MC_CELL_SKIP, scale);

	if(width>m_lineWidth)
	  width=m_lineWidth;
      }
  }
  return m_lineWidth;
}


bool CellList::IsEditable(Cell *SelectionStart)
{
  if(SelectionStart->IsComment()) return true;
  
  // Next we test if this is the first input cell after the prompt.
  // If there is no cell before this one we can already return.

  if(SelectionStart==front()) return false;
  
  Cell *CellInFrontOfSelection=SelectionStart;
  CellInFrontOfSelection--;
    
  if (
      (SelectionStart->GetType() == MC_TYPE_INPUT)  &&
      (CellInFrontOfSelection->GetType() == MC_TYPE_MAIN_PROMPT)
      )
    return true;
  else
    return false;
}

void CellList::SetParent(Cell *parent)
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->SetParent(parent);
}

void CellList::Unbreak()
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->Unbreak();
}

void CellList::RecalculateSize(CellParser& parser, int fontsize)
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->RecalculateSize(parser,fontsize);
}

void CellList::ResetData()
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->ResetData();
}

void CellList::RecalculateWidths(CellParser& parser, int fontsize)
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->RecalculateWidths(parser,fontsize);
}

void CellList::DrawBoundingBox(wxDC& dc, int border)
{
  wxRect rect = GetRect();
  int x = rect.GetX(), y = rect.GetY();
  int width = rect.GetWidth(), height = rect.GetHeight();
  dc.DrawRectangle(x - border, y - border, width + 2*border, height + 2*border);
}

bool CellList::IsCompound()
{
  bool retval=false;
  for(iterator i=begin();i!=end();i++)
    if ((*i)->IsOperator())
      {
	retval=true;break;
      }
  return(retval);
}


wxRect CellList::GetRect()
{
  Cell *LineBegin=front();
  return wxRect(
		LineBegin->m_currentPoint.x,
		LineBegin->m_currentPoint.y - LineBegin->GetMaxCenter(),
		GetLineWidth(1.0),
		LineBegin->GetMaxHeight());
}

CellList* CellList::Copy()
{
  CellList *retval;

  for(iterator i=begin();i!=end();i++)
    retval->AppendCell((*i)->Copy());

  return retval;
}
  

bool CellList::ContainsRect(wxRect& sm)
{
  wxRect big = GetRect();
  if (big.x <= sm.x &&
          big.y <= sm.y &&
          big.x + big.width >= sm.x + sm.width &&
          big.y + big.height >= sm.y + sm.height)
    return true;
  return false;
}

void CellList::Draw(CellParser& parser, wxPoint point, int fontsize)
{
  Cell *tmp=front();
  
  while (tmp != NULL)
  {
    double scale = parser.GetScale();
    point.x += tmp->GetWidth() + SCALE_PX(MC_CELL_SKIP, scale);
    tmp->Draw(parser, point, fontsize);
    tmp=tmp->m_nextToDraw;
  }
}

wxString CellList::ToString()
{
  wxString retval;
  for(iterator i=begin();i!=end();i++)
    {
      if((*i)->ForceBreakLineHere())
	retval+="\n";
      retval+=(*i)->ToString();
    }
}

wxString CellList::ToTeX()
{
  wxString retval;
  for(iterator i=begin();i!=end();i++)
    {
      retval+=(*i)->ToTeX();
    }
}

wxString CellList::ToXML()
{
  wxString retval;
  for(iterator i=begin();i!=end();i++)
    {
      if((*i)->ForceBreakLineHere())
	retval+="\n";
      retval+=(*i)->ToXML();
    }
}

void CellList::Clear()
{
  for(iterator i=begin();i!=end();i++)
    if(*i!=NULL)
      {
	delete *i;
	*i=NULL;
      }
  
}

CellList::~CellList()
{
  // Free all memory occupied by the cells the list manages pointers to. 
  Clear();
}
