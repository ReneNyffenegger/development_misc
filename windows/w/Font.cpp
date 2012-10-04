/* 
   Font.cpp

   Copyright (C) 2002-2004 René Nyffenegger

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

#include "Font.h"

Font::Font(STD_STR const& name, int size, bool bold, bool italic, bool underlined) {
  font_ = ::CreateFont(size, 0, 0, 0, bold? FW_BOLD : FW_NORMAL, italic, underlined, false,
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY,
      FF_DONTCARE,
      name.c_str());

  if (!font_) {
    throw "Couldn't create font";
  }
}

Font::~Font() {
  ::DeleteObject(font_);
}
