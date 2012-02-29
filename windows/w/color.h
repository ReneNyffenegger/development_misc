/* 
   Color.h

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

#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <sstream>
#include <windows.h>

class Color {
  public:
    Color(unsigned char red, unsigned char green, unsigned char blue);
    Color(COLORREF);
    Color(const std::string&);
  private:
    friend class DC;
    COLORREF color_;
};

#endif
