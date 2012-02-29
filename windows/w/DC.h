/* 
   File DC.h: Copyright (C) René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/


#ifndef DC_H__
#define DC_H__

class Brush;
class Font;
class Pen;
class Region;
class Color;

#include <string>
#include <sstream>
#include <windows.h>

#include "STD_STR.h"

/*! DC is a wrapper class for the Device Context functions (Find them
 *  here: http://msdn.microsoft.com/library/en-us/gdi/devcons_7e2b.asp?frame=true) */
class DC {
  public:
    DC(HDC);
    virtual ~DC();

    /*! \name Printing Text onto the Device Context.
     *        The following methods print a text at the
     *        indicated coordinates (x,y). Use DC::TextAlign
     *        in order to influence the meaning of the
     *        coordinates.
     *        The call results in using ::TextOut
     * */
    //@{
    /*! \short Print a wide character text */
    void Text(int x, int y, const STD_STR& text);

    /*! \short Prints a text in a specified, changes then back to the Color that was in use when 
               #Text was called */
    void Text(int x, int y, const STD_STR& text, const Color&);

    /*! \short Print an Integer */
    void Text(int x, int y, int i);

    //@}

    /*! \name Doing lines and such
     *        The following methods are used in order to draw lines onto a device context */
    //@{

    void Move(int x, int y);

    void Line(int xTo, int yTo);

    //@}
    enum v_textalignment {top  = TA_TOP , baseline = TA_BASELINE, bottom = TA_BOTTOM};
    enum h_textalignment {left = TA_LEFT, center   = TA_CENTER,   right  = TA_RIGHT};

    /*! \short calls SetTextAlign.
     *         Use this method in order to influence the meaning of the coordinates given to DC::Text.*/
    void TextAlign(v_textalignment, h_textalignment);

    /*! \short calls SetTextAlign with TA_UPDATECP */
    void TextAlignUpdated();

    /*! \short calls SetBkColor */
    void BackgroundColor(unsigned char red, unsigned char green, unsigned char blue);

    /*! \short Sets the Color in which the following Text is printed when Text is called. */
    void TextColor(const Color&);

    /*! \short Get the current color in which text is printed */
    Color TextColor() const;

    /*! \short calls SetBkMode with OPAQUE (if b is true) or TRANSPARENT (if b is false)*/
    void DrawOpaque(bool b);

    operator HDC () const;

    /*! \name Methods that encapsulate SelectObject (described
     *        at http://msdn.microsoft.com/library/en-us/gdi/devcons_9v3o.asp?frame=true */
    //@{
    Brush  Select(Brush&     );
    Font   Select(Font const&);
    Pen    Select(Pen&       );
    Region Select(Region&    );
    //@}

  protected:
    HDC dc_;
};

#endif

