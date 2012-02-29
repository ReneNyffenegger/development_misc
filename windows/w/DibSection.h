/* 
   DibSection.h

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

#ifndef DIB_SECTION_H_
#define DIB_SECTION_H__

class DC;

#include "Bitmap.h"

class DibSection : public Bitmap {
  public:
    DibSection(int bmpWidth, int bmpHeight);
    DibSection();
   ~DibSection();

    inline void PixelAt(unsigned int x, unsigned int y, unsigned int color);
 
    void BitBltTo  (DC const& dcTo, int xTo, int yTo);
    void BitBltFrom(DC const& dcFrom, int xTo, int yTo, int width, int height);
 
    bool Size(int bmpWidth, int bmpHeight);

  private:
    char*   theBits_;

    /*! todo bmpWidth_ and such to the base class! */
    int     bmpWidth_;
    int     bmpHeight_;

    int     lineLength_;
};

// 4273 is inconsistent dll linkage.  dllexport assumed.
//#pragma warning (push)
//#pragma warning (disable: 4273)
void DibSection::PixelAt(unsigned int x, unsigned int y, unsigned int color) {
//#pragma warning (pop)

#ifdef _DEBUG
  if (x>bmpWidth_) {
    throw "x too large in PixelAt";
  }
  if (y>bmpHeight_) {
    throw "y too large in PixelAt";
  }
#endif

  theBits_[y*lineLength_ + 3*x + 0] = (color & 0xff0000) >> 16;
  theBits_[y*lineLength_ + 3*x + 1] = (color & 0x00ff00) >>  8;
  theBits_[y*lineLength_ + 3*x + 2] = (color & 0x0000ff) >>  0;
}

#endif
