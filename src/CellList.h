#include "Cell.h"
#include <list>
#include <iterator>

class CellList:public std::list<Cell *>
{
  
public:
  CellList();
  ~CellList();
  virtual void SetParent(Cell *parent);
  virtual void Unbreak();
  virtual void ResetData();
  virtual void Draw(CellParser& parser, wxPoint point, int fontsize);
  virtual void RecalculateSize(CellParser& parser, int fontsize);
  virtual void RecalculateWidths(CellParser& parser, int fontsize);

  //! Get the distance between the top and the center of the line.
  int GetMaxCenter();
  //! Get the distance between the bottom and the center of the line.
  int GetMaxDrop();
  //!  Get the maximum hight of cells in line.
  int GetMaxHeight();

  /*! Get the width this list of cells would have if there weren't any linebreaks.
    
    The value this function returns is cached in the variable m_fullWidth.
  */
  int GetFullWidth(double scale);
  
  /*! Get the width of this list of cells including linebreaks.
   */
  
  int GetLineWidth(double scale);
  
  virtual wxString ToString();
  virtual wxString ToTeX();
  virtual wxString ToXML();
  virtual CellList* Copy();
  //! Is this a comment or the beginning of a list of input cells?
  bool IsEditable(Cell *SelectionStart);
  /*! Append a cell to the list.

    Just appending the cell with std::list's methods doesn't add it to 
    m_nextToDraw so this function is necessary.

    \todo Did change the logic here somehow. Is this function still valid?.
   */
  void AppendCell(Cell *p_next);

  //! Empty this list freeing the memory occupied by all cells it manages pointers to.
  void Clear();

  virtual wxRect GetRect();
  /*! Draw a rectangle that shows the bounding box of this line

    \todo The code of this method is identical to the code of the same method 
    for cells. Why do we still need to add it to CellList.cpp and CellList.h?
  */
  virtual void DrawBoundingBox(wxDC& dc, int border);

  /*! Does this object overlap the given rectangle?

    \todo The code of this method is identical to the code of the same method 
    for cells. Why do we still need to add it to CellList.cpp and CellList.h?
  */
  virtual bool ContainsRect(wxRect& sm);

  //! Do we have any operators in this cell list?
  bool IsCompound();

  
 private:

  /*! Caches the width of the list starting with this cell.

    - Will contain -1, if it has not yet been calculated.
    - Won't be recalculated on appending new cells to the list.
  */
  int m_fullWidth;
  /*! Caches the width of the rest of the line this cell is part of.

    - Will contain -1, if it has not yet been calculated.
    - Won't be recalculated on appending new cells to the list.
  */  
  int m_lineWidth;

};
