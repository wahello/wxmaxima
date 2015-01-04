#include "Cell.h"
#include <list>
#include <iterator>

class CellList:public std::list<Cell *>
{
  
public:
  CellList();
  ~CellList();
  virtual void SetParent(Cell *parent);
  //! Unbreak all cells in the list.
  virtual void Unbreak();
  //! Unbreak the current cell.
  virtual void Unbreak(Cell *cell);
  virtual void ResetData();
  virtual void Draw(CellParser& parser, wxPoint point, int fontsize);
  virtual void RecalculateSize(CellParser& parser, int fontsize);
  virtual void RecalculateWidths(CellParser& parser, int fontsize);
  /*! Returns an iterator that points to the list element cell

    If the element isn't found in the list this is deemed to be a bug in the
    program and therefore is caught by an assert macro.
   */
  CellList::iterator ListElement(Cell *cell);

  //! Get the distance between the top and the center of the line.
  int GetMaxCenter(Cell *LineStart);
  //! Get the distance between the bottom and the center of the line.
  int GetMaxDrop(Cell *LineStart);
  //!  Get the maximum hight of cells in line.
  int GetMaxHeight(Cell *LineStart);

  /*! Get the width this list of cells would have if there weren't any linebreaks.
    
    The value this function returns is cached in the variable m_fullWidth.
  */
  int GetFullWidth(double scale);
  
  /*! Get the width of the bounding box occupied by this list of cells.
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

/*! Find the first cell in rectangle rect in this line.

  \return the first cell that intersects the given rectangle or NULL if there isn't such a cell.
 */
  Cell *SelectFirst(wxRect& rect);

  /*! Find the last cell in rectangle rect in this line.

  \return the last cell that intersects the given rectangle or NULL if there isn't such a cell.
 */
  Cell *SelectLast(wxRect& rect);

 private:
  /*! Caches the width of the bounding box occupied by this list of cells.

    - Will contain -1, if it has not yet been calculated.
    - Won't be recalculated on appending new cells to the list.
  */  
  int m_lineWidth;

  /*! Caches the width of the list starting with this cell.

    - Will contain -1, if it has not yet been calculated.
    - Won't be recalculated on appending new cells to the list.
  */
  int m_fullWidth;
};
