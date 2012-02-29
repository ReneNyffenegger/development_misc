/* 
   Pen.h

   Copyright (C) René Nyffenegger

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

#ifndef PEN_H_
#define PEN_H_

#include <string>
#include <sstream>
#include <windows.h>

class Pen {

  public:
    enum style {
      solid      = PS_SOLID,
      dashed     = PS_DASH,
      dotted     = PS_DOT,
      dashdot    = PS_DASHDOT,
      dashdotdot = PS_DASHDOTDOT,
      invisible  = PS_NULL,
      inside     = PS_INSIDEFRAME,
    };

  /*! \short This constructor creates a pen, using CreatePen, described at
   * http://msdn.microsoft.com/library/en-us/gdi/pens_9wha.asp?frame=true */
  Pen(unsigned char r, unsigned char g, unsigned char b, unsigned int width=1, style st=solid);

 ~Pen();

  protected:
    friend class DC;
    Pen(HPEN p) : pen_(p){};
    operator HPEN() const {return pen_;};

  private:
    HPEN pen_;
};

#endif
