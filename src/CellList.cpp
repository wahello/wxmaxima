#include "CellList.h"
CellList::CellList()
{
  m_fullWidth = -1;
  m_lineWidth = -1;
}

void CellList::AppendCell(Cell *p_next)
{
  // If there is nothing to append we return immediately.
  if (p_next == NULL) return ;

  // We want to app end something. Therefore the size information has to
  // be recalculated.
  ResetData();

  Cell *tmp=back();
  
  if(!empty())
    (*end())->m_nextToDraw=p_next;
  push_back(p_next);
  
  p_next->m_previousToDraw=tmp;
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

int CellList::GetMaxCenter(Cell *LineStart)
{
  // -1 means we need to recalculate this value.
  if (LineStart->m_maxCenter == -1)
  {
      
    Cell *tmp=front();
    int max_Center=0;
    
    // Find the last element in the order they will be drawn so we can iterate
    // backwards from there.
    while(tmp->m_nextToDraw)tmp=tmp->m_nextToDraw;

    // Now we iterate backwards through the list
    // Normally this should look like the following:
    //    for (std::list<int>::reverse_iterator i = s.rbegin(); i != s.rend(); ++i)
    // But this time we have to iterate by hand: It might happen that we draw
    // things in a different order than specified by in the list.
    while (tmp!=NULL)
      {
	// Determine if we got a new maximum center value
	if(max_Center>tmp->GetCenter())
	  max_Center=tmp->GetCenter();

	// Save the value in the cell
	tmp->m_maxCenter=max_Center;

	// If this cell begins with a linebreak the maximum center value calculation
	// restarts with 0 for the previous cell
	if(tmp->m_isBroken)
	  max_Center=0;

	// If I didn't get something wrong the old code was able to add
	// inconsistencies here. So we better check...
	if(tmp->m_previousToDraw)
	  wxASSERT_MSG(
		       tmp==(tmp->m_previousToDraw)->m_nextToDraw,
		       "m_previousToDraw and m_nextToDraw are inconsistent"
		       );

	// Go to the element that is drawn prior to this one.
	tmp=tmp->m_previousToDraw;
      }
  }
  return LineStart->m_maxCenter;
}

int CellList::GetMaxDrop(Cell *LineStart)
{
  // -1 means we need to recalculate this value.
  if (LineStart->m_maxDrop == -1)
  {
      
    Cell *tmp=front();
    int max_Drop=0;
    
    // Find the last element in the order they will be drawn so we can iterate
    // backwards from there.
    while(tmp->m_nextToDraw)tmp=tmp->m_nextToDraw;

    // Now we iterate backwards through the list
    // Normally this should look like the following:
    //    for (std::list<int>::reverse_iterator i = s.rbegin(); i != s.rend(); ++i)
    // But this time we have to iterate by hand: It might happen that we draw
    // things in a different order than specified by in the list.
    while (tmp!=NULL)
      {
	// Determine if we got a new maximum center value
	if(max_Drop>tmp->GetDrop())
	  max_Drop=tmp->GetDrop();

	// Save the value in the cell
	tmp->m_maxDrop=max_Drop;

	// If this cell begins with a linebreak the maximum center value calculation
	// restarts with 0 for the previous cell
	if(tmp->m_isBroken)
	  max_Drop=0;

	// If I didn't get something wrong the old code was able to add
	// inconsistencies here. So we better check...	
	if(tmp->m_previousToDraw)
	  wxASSERT_MSG(
		       tmp==(tmp->m_previousToDraw)->m_nextToDraw,
		       "m_previousToDraw and m_nextToDraw are inconsistent"
		       );
	
	// Go to the element that is drawn prior to this one.
	tmp=tmp->m_previousToDraw;
      }
  }
  return LineStart->m_maxDrop;
}

int CellList::GetMaxHeight(Cell *LineStart)
{
  return GetMaxCenter(LineStart) + GetMaxDrop(LineStart);
}

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

CellList::iterator CellList::ListElement(Cell *cell)
{
  iterator retval;
  while((*retval!=cell)&&(retval!=end()))
    retval++;
  wxASSERT_MSG(
	       *retval==cell,
	       "Cell wasn't part of the list it was supposed to be in."
	       );
  return(retval);
}

bool CellList::IsEditable(Cell *SelectionStart)
{
  if(SelectionStart->IsComment()) return true;
  
  // Next we test if this is the first input cell after the prompt.
  // If there is no cell before this one we can already return.

  if(SelectionStart==front()) return false;

  // Search the list of cells for the current cell.
  iterator CellInFrontOfSelection=ListElement(SelectionStart);
  CellInFrontOfSelection--;
    
  if (
      (SelectionStart->GetType() == MC_TYPE_INPUT)  &&
      ((*CellInFrontOfSelection)->GetType() == MC_TYPE_MAIN_PROMPT)
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

void CellList::RecalculateSize(CellParser& parser, int fontsize)
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->RecalculateSize(parser,fontsize);
}

void CellList::ResetData()
{ 
  m_fullWidth = -1;
  m_lineWidth = -1;
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

Cell *CellList::SelectFirst(wxRect& rect)
{

  iterator i=begin();

  while((!rect.Intersects((*i)->GetRect()))&&(i!=end()))
	i++;

  if(rect.Intersects((*i)->GetRect()))
    return(*i);
  else
    return(NULL);
}

void CellList::Unbreak(Cell *cell)
{

  iterator currentelement=ListElement(cell);
  
  cell->ResetData();
  cell->m_isBroken = false;
  if(currentelement==end())
    cell->m_nextToDraw = NULL;
  else
    cell->m_nextToDraw = *(++currentelement);
  if (cell->m_nextToDraw != NULL)
    cell->m_nextToDraw->m_previousToDraw = cell;
}

void CellList::Unbreak()
{ 
  for(iterator i=begin();i!=end();i++)
    (*i)->Unbreak();
}

Cell *CellList::SelectLast(wxRect& rect)
{

  iterator i=end();

  while((!rect.Intersects((*i)->GetRect()))&&(i!=begin()))
	i--;

  if(rect.Intersects((*i)->GetRect()))
    return(*i);
  else
    return(NULL);
}

void CellList::SelectRect(wxRect& rect, Cell** first, Cell** last)
{
  Cell *Begin=SelectFirst(rect);
  Cell *End=  SelectLast(rect);

  if((Begin!=NULL)&&(End!=NULL))
    *first=*last=NULL;
  else
    {
      *first=Begin;
      *last=End;
    }
}
