// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//  Copyright (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
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

/*!\file
  
  The definition of the base class of all cells.
 */

#ifndef MATHCELL_H
#define MATHCELL_H

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))
#define ABS(a) ((a)>=0 ? (a) : -(a))
#define SCALE_PX(px, scale) ((int)((double)((px)*(scale)) + 0.5))

#define MC_CELL_SKIP 0
#define MC_BASE_INDENT 12
#define MC_LINE_SKIP 2
#define MC_TEXT_PADDING 1

#define MC_GROUP_SKIP 20
//! The horizontal amount the worksheet is indented by  
#define MC_GROUP_LEFT_INDENT 15

//! The width of the horizontally-drawn cursor
#define MC_HCARET_WIDTH 25

#if defined __WXMAC__
 #define MC_EXP_INDENT 2
 #define MC_MIN_SIZE 10
 #define MC_MAX_SIZE 36
#else
 #define MC_EXP_INDENT 4
 #define MC_MIN_SIZE 8
 #define MC_MAX_SIZE 36
#endif

#include <wx/wx.h>
#include "CellParser.h"
#include "TextStyle.h"

/*! The supported types of math cells
 */
enum {
  MC_TYPE_DEFAULT,
  MC_TYPE_MAIN_PROMPT,
  MC_TYPE_PROMPT,
  MC_TYPE_LABEL,       //!< An output label generated by maxima
  MC_TYPE_INPUT,       //!< An input cell
  MC_TYPE_ERROR,       //!< An error output by maxima
  MC_TYPE_TEXT,        //!< Text that isn't passed to maxima
  MC_TYPE_SUBSECTION,  //!< A subsection name
  MC_TYPE_SUBSUBSECTION,  //!< A subsubsection name
  MC_TYPE_SECTION,     //!< A section name
  MC_TYPE_TITLE,       //!< The title of the document
  MC_TYPE_IMAGE,       //!< An image
  MC_TYPE_SLIDE,       //!< An animation created by the with_slider_* maxima commands
  MC_TYPE_GROUP        //!< A group cells that bundles several individual cells together
};

/*!
  The base class all cell types are derived from

  Every MathCell is part of a double-linked lists: A MathCell does have 
  a member that points to the previous item (or contains a NULL for the head node 
  of the list) and a member that points to the next cell (or contains a NULL if 
  this is the end node of a list).
  Also every list of MathCells can be a branch of a tree since every math cell contains
  a pointer to its parent group cell.

  Besides the cell types that are directly user visible there are cells for several
  kinds of items that are displayed in a special way like abs() statements (displayed
  as horizontal rules), subscripts, superscripts and exponents.
  Another important concept realized realized by a clas derived from this one is 
  the group cell that groups all things that are foldable in the gui like:
   - A combination of maxima input with the output, the input prompt and the output 
     label.
   - A chapter or a section and
   - Images with their title (or the input cells that generated them)
   .

  \attention Derived classes must test if m_next equals NULL and if it doesn't
  they have to delete() it.
 */
class MathCell
{
public:
  MathCell();
  virtual ~MathCell();  
  /*! Free all memory directly referenced by the contents of this cell

    This command (and the celltype-specific versions of the derived
    classes) are internally used by the DestroyTree() functions that
    free the complete list of cells.
    \attention This function Doesn't free the other cells of the list
    that is started by this cell.
   */
  virtual void Destroy() = 0;

  //! Delete this cell and all cells that follow it in the list.
  void DestroyList();
  
  /*! Add a cell to the end of the list this cell is part of
    
    \param p_next The cell that will be appended to the list.
   */
  void AppendCell(MathCell *p_next);

  //! 0 for ordinary cells, 1 for slide shows and diagrams displayed with a 1-pixel border
  int m_imageBorderWidth;
  //! Do we want this cell to start with a linebreak?
  void BreakLine(bool breakLine) { m_breakLine = breakLine; }
  //! Do we want this cell to start with a pagebreak?
  void BreakPage(bool breakPage) { m_breakPage = breakPage; }
  //! Are we allowed to break a line here?
  bool BreakLineHere();
  //! Does this cell begin begin with a manual linebreak?
  bool ForceBreakLineHere() { return m_forceBreakLine; }
  //! Does this cell begin begin with a manual page break?  
  bool BreakPageHere() { return m_breakPage; }
  virtual bool BreakUp() { return false; }
  /*! Is a part of this cell inside a certain rectangle?

    \param big The rectangle to test for collision with this cell
    \param all
     - true means test this cell and the ones that are following it in the list
     - false means test this cell only.
   */
  bool ContainsRect(wxRect& big, bool all = true);
  /*! Is a given point inside this cell?

    \param point The point to test for collision with this cell
   */
  bool ContainsPoint(const wxPoint& point)
  {
    return GetRect().Contains(point);
  }
  void CopyData(MathCell *s, MathCell *t);

  /*! Clears memory from cached items automatically regenerated when the cell is drawn
    
    The scaled version of the image will be recreated automatically once it is 
    needed.
   */
  virtual void ClearCache(){}

  /*! Clears the cache of the whole list of cells starting with this one.

    For details see ClearCache().
   */
  void ClearCacheList();

  /*! Draw this cell

    \param point The x and y position this cell is drawn at
    \param fontsize The font size that is to be used
    \param all
     - true: the whole list of cells has to be drawn starting with this one
     - false: only this cell has to be drawn
   */
  virtual void Draw(CellParser& parser, wxPoint point, int fontsize);
  /*! Draw this list of cells

    \param point The x and y position this cell is drawn at
    \param fontsize The font size that is to be used
    \param all
     - true: the whole list of cells has to be drawn starting with this one
     - false: only this cell has to be drawn
   */
  void DrawList(CellParser& parser, wxPoint point, int fontsize);
  /*! Draw the bounding box of this cell or this list of cells

    \param all
     - true:  Draw the bounding box around this list of cells
     - false: Draw the bounding box around this cell only
     \param border The width of the border in pixels
     \param dc Where to draw the box.
  */
  void DrawBoundingBox(wxDC& dc, bool all = false, int border = 0);
  bool DrawThisCell(CellParser& parser, wxPoint point);

  /*! Insert (or remove) a forced linebreak at the beginning of this cell.

    \param force
     - true: Insert a forced linebreak
     - false: Remove the forced linebreak
   */
  void ForceBreakLine(bool force) { m_forceBreakLine = m_breakLine = force; }

  //! Get the total height of this cell
  int GetHeight() { return m_height; }
  //! Get the width of this cell
  int GetWidth() { return m_width; }
  /*! Get the distance between the top and the center of this cell.

    Remember that (for example with double fractions) the center does not have to be in the 
    middle of a cell even if this object is --- by definition --- center-aligned.
   */
  int GetCenter() { return m_center; }
  /*! Get the distance between the center and the bottom of this cell


    Remember that (for example with double fractions) the center does not have to be in the 
    middle of a cell even if this object is --- by definition --- center-aligned.
   */
  int GetDrop() { return m_height - m_center; }

  /*! 
    Returns the type of this cell.
   */
  int GetType() { return m_type; }
  /*! Returns the maximum distance between center and bottom of this line

    Note that the center doesn't need to be exactly in the middle of an object.
    For a fraction for example the center is exactly at the middle of the 
    horizontal line.
   */
  int GetMaxDrop();
  /*! Returns the maximum distance between top and center of this line

    Note that the center doesn't need to be exactly in the middle of an object.
    For a fraction for example the center is exactly at the middle of the 
    horizontal line.
  */
  int GetMaxCenter();
  /*! Returns the total height of this line

    Returns GetMaxCenter()+GetMaxDrop()
   */
  int GetMaxHeight();
  //! How many pixels would this list of cells be wide if we didn't introduce line breaks?
  int GetFullWidth(double scale);
  /*! How many pixels is this list of cells wide?

    This command returns the real line width when all line breaks are really performed. 
    See GetFullWidth().
   */
  int GetLineWidth(double scale);
  //! Get the x position of the top left of this cell
  int GetCurrentX() { return m_currentPoint.x; }
  //! Get the y position of the top left of this cell
  int GetCurrentY() { return m_currentPoint.y; }
  /*! Get the smallest rectangle this cell fits in

    \param all
      - true: Get the rectangle for this cell and the ones that follow it in the list of cells
      - false: Get the rectangle for this cell only.
   */
  virtual wxRect GetRect(bool all = false);
  virtual wxString GetDiffPart();
  /*! Recalculate the height of the cell and the difference between top and center

    Should set: m_height, m_center.
  */
  virtual void RecalculateSize(CellParser& parser, int fontsize) { };
  //! Recalculate the height of this list of cells 
  void RecalculateSizeList(CellParser& parser, int fontsize);
  //! Marks all widths of this cell as to be recalculated on query.
  virtual void RecalculateWidths(CellParser& parser, int fontsize);
  //! Marks all widths of this list as to be recalculated on query.
  void RecalculateWidthsList(CellParser& parser, int fontsize);
  //! Mark all cached size information as "to be calculated".
  void ResetData();
  //! Mark the cached height informations as "to be calculated".
  void ResetSize() { m_width = m_height = -1; }

  void SetSkip(bool skip) { m_bigSkip = skip; }
  //! Sets the text style according to the type
  void SetType(int type);
  int GetStyle(){ return m_textStyle; }	//l'ho aggiunto io

  void SetPen(CellParser& parser);
  //! Mark this cell as highlighted (e.G. being in a maxima box)
  void SetHighlight(bool highlight) { m_highlight = highlight; }
  //! Is this cell highlighted (e.G. inside a maxima box)
  bool GetHighlight() { return m_highlight; }
  virtual void SetExponentFlag() { }
  virtual void SetValue(wxString text) { }
  virtual wxString GetValue() { return wxEmptyString; }

  //! Get the first cell in this list of cells
  MathCell *first();
  //! Get the last cell in this list of cells
  MathCell *last();
  
  void SelectRect(wxRect& rect, MathCell** first, MathCell** last);
  void SelectFirst(wxRect& rect, MathCell** first);
  void SelectLast(wxRect& rect, MathCell** last);
  /*! Select a rectangle that is created by a cell inside this cell.

    \attention This method has to be overridden by children of the 
    MathCell class.
  */
  virtual void SelectInner(wxRect& rect, MathCell** first, MathCell** last);

  virtual bool IsOperator();
  bool IsCompound();
  virtual bool IsShortNum() { return false; }

  MathCell* GetParent();

  //! For the bitmap export we sometimes want to know how big the result will be...
  struct SizeInMillimeters
  {
  public:
    double x,y;
  };

    //! Returns the list's representation as a string.
  virtual wxString ListToString();
  //! Convert this list to its LaTeX representation
  virtual wxString ListToTeX();
  //! Convert this list to an representation fit for saving in a .wxmx file
  virtual wxString ListToXML();
  //! Returns the cell's representation as a string.
  virtual wxString ToString();
  //! Convert this cell to its LaTeX representation
  virtual wxString ToTeX();
  //! Convert this cell to an representation fit for saving in a .wxmx file
  virtual wxString ToXML();
  //! The height of this cell

  void UnsetPen(CellParser& parser);
  /*! Unbreak this cell

    Some cells have different representations when they contain a line break.
    Examples for this are fractions or a set of parenthesis.

    This function tries to return a cell to the single-line form.
   */
  virtual void Unbreak();
  /*! Unbreak this line

    Some cells have different representations when they contain a line break.
    Examples for this are fractions or a set of parenthesis.

    This function tries to return a list of cells to the single-line form.
  */
  virtual void UnbreakList();

  /*! The next cell in the list of cells

    Reads NULL, if this is the last cell of the list.
   */
  MathCell *m_next;
  /*! The previous cell in the list of cells
    
    Reads NULL, if this is the first cell of the list.    
   */
  MathCell *m_previous;
  /*! The next cell to draw
    
    Normally things are drawn in the order in which they appear in this list.
    But in special cases (for example if a fraction is broken into several lines
    and therefore cannot be displayed as a fraction) the order in which items are
    drawn varies. Each cell is therefore part of a second list made up by 
    m_nextToDraw and m_previousToDraw.
   */
  MathCell *m_nextToDraw;
  /*! The previous cell to draw
    
    Normally things are drawn in the order in which they appear in this list.
    But in special cases (for example if a fraction is broken into several lines
    and therefore cannot be displayed as a fraction) the order in which items are
    drawn varies. Each cell is therefore part of a second list made up by 
    m_nextToDraw and m_previousToDraw.
   */
  MathCell *m_previousToDraw;
  /*! The point in the work sheet at which this cell begins.

    The begin of a cell is defined as 
     - x=the left border of the cell
     - y=the vertical center of the cell. Which (per example in the case of a fraction)
       might not be the physical center but the vertical position of the horizontal line
       between nummerator and denominator.
  */
  wxPoint m_currentPoint;  
  bool m_bigSkip;
  //! true means: Add a linebreak to the end of this cell.
  bool m_isBroken;
  /*! True means: This cell is a multiplication sign that isn't drawn.

    Currently only the centered dots for multiplications fall in this category.
   */
  bool m_isHidden;
  /*! Determine if this cell contains text that won't be passed to maxima

    \return true, if this is a text cell, a title cell, a section, a subsection or a subsubsection cell.
   */
  bool IsComment()
  {
    return m_type == MC_TYPE_TEXT || m_type == MC_TYPE_SECTION ||
           m_type == MC_TYPE_SUBSECTION || m_type == MC_TYPE_SUBSUBSECTION ||
           m_type == MC_TYPE_TITLE;
  }
  bool IsEditable(bool input = false)
  {
    return (m_type == MC_TYPE_INPUT  &&
            m_previous != NULL && m_previous->m_type == MC_TYPE_MAIN_PROMPT)
         || (!input && IsComment());
  }
  virtual void ProcessEvent(wxKeyEvent& event) { }
  virtual bool ActivateCell() { return false; }
  virtual bool AddEnding() { return false; }
  virtual void SelectPointText(wxDC &dc, wxPoint& point) { }
  virtual void SelectRectText(wxDC &dc, wxPoint& one, wxPoint& two) { }
  virtual void PasteFromClipboard(bool primary = false) { }
  virtual bool CopyToClipboard() { return false; }
  virtual bool CutToClipboard() { return false; }
  virtual void SelectAll() { }
  virtual bool CanCopy() { return false; }
  virtual void SetMatchParens(bool match) { }
  virtual wxPoint PositionToPoint(CellParser& parser, int pos = -1) { return wxPoint(-1, -1); }
  virtual bool IsDirty() { return false; }
  virtual void SwitchCaretDisplay() { }
  virtual void SetFocus(bool focus) { }
  void SetForeground(CellParser& parser);
  virtual bool IsActive() { return false; }
  /*! Define which GroupCell is the parent of this cell.
    
    By definition every math cell is part of a group cell.
    So this function has to be called on every math cell. Also if a
    derived class defines a cell type that does include sub-cells 
    (One example would be the argument of a sqrt() cell) the derived
    class has to take care that the subCell's SetParent is called when
    the cell's SetParent is called.
   */
  virtual void SetParent(MathCell *parent) {m_group = parent;};
  //! Define which GroupCell is the parent of all cells in this list
  void SetParentList(MathCell *parent);
  void SetStyle(int style) { m_textStyle = style; }
  bool IsMath();
  void SetAltCopyText(wxString text) { m_altCopyText = text; }
  /*! Attach a copy of the list of cells that follows this one to a cell
    
    Used by MathCell::Copy() when the parameter <code>all</code> is true.
  */
  MathCell *CopyList();
  /*! Copy this cell
    
    This method is used by CopyList() which creates a copy of a cell tree. 
    
    \return A copy of this cell without the rest of the list this cell is part 
    from.
  */
  virtual MathCell* Copy() = 0;
  /*! Do we want to begin this cell with a center dot if it is part of a product?

    Maxima will represent a product like (a*b*c) by a list like the following:
    [*,a,b,c]. This would result us in converting (a*b*c) to the following LaTeX
    code: \left(\cdot a \cdot b \cdot c\right) which obviously is one \cdot too
    many => we need parenthesis cells to set this flag for the first cell in 
    their "inner cell" list.
   */
  bool m_SuppressMultiplicationDot;

  /*! Set the size of the canvas our cells have to be drawn on

   */
  void SetCanvasSize(wxSize size) { m_canvasSize = size; }
protected:
  /*! The GroupCell this list of cells belongs to.
    
    Reads NULL, if no parent cell has been set - which is treated as an Error by GetParent():
    every math cell has a GroupCell it belongs to.
  */
  MathCell *m_group;
  //! The size of the canvas our cells have to be drawn on
  static wxSize m_canvasSize;
  int m_height;
  //! The width of this cell
  int m_width;
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
  int m_center;
  int m_maxCenter;
  int m_maxDrop;
  int m_type;
  int m_textStyle;

  //! Does this cell begin with a forced page break?
  bool m_breakPage;
  //! Are we allowed to add a linee break before this cell?
  bool m_breakLine;
  //! true means we forcce this cell to begin with a line break.  
  bool m_forceBreakLine;
  bool m_highlight;
  wxString m_altCopyText; // m_altCopyText is not check in all cells!
};

#endif // MATHCELL_H
