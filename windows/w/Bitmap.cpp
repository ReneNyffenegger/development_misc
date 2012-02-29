/* 
   Bitmap.h

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

#include "Bitmap.h"

/*! \page bmps_in_memory drawing on Bitmaps in Memory
 *
 *   If you want to use bitmaps in memory and draw upon them,
 *   you have to follow these steps:
 *
 *   \li 1 Allocate a MemoryDC (this is a memory device context used for the drawing operations
 *         which a device context provides)
 *   \li 2 Create a CompatibleBitmap
 *   \li 3 Select this compatible Bitmap into the memory device context (the bitmap now becomes
 *         the surface for the drawing operations made onto the device context. Keep the
 *         return value for unselecting it again
 *   \li 4 do your drawings
 *   \li 5 unselect the selected bitmap
 * 
 *
 * See the following code for an example.
 *
 *   \code
 
  MemoryDC memDc;
  CompatibleBitmap compBmp(memDc, width, height);
  Bitmap oldBmp = memDc.Select(compBmp);
       
  // Your drawing operations go here
 
  memDc.Select(oldBmp);

 *   \endcode
 *
 *
 *
 */

Bitmap::Bitmap() : bitmap_(0) {}

Bitmap::Bitmap(std::string const& file_name) {
  bitmap_ = static_cast<HBITMAP>(::LoadImage(0, file_name.c_str(), IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION));
}

Bitmap::Bitmap(HBITMAP bmp) : bitmap_(bmp) {

}

Bitmap::operator HBITMAP() const {
  return bitmap_;
}

