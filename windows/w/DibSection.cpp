/* 
   DibSection.cpp

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

#include "DibSection.h"
#include "DC.h"
#include "MemoryDC.h"
#include "win32_LastError.h"

DibSection::DibSection(int bmpWidth, int bmpHeight) : 
  Bitmap     (), 
  bmpWidth_  (0), 
  bmpHeight_ (0), 
  lineLength_(0) 
{
  Size(bmpWidth, bmpHeight);
}

DibSection::DibSection() : Bitmap(), theBits_(0), bmpWidth_(0), bmpHeight_(0), lineLength_(0) {}

bool DibSection::Size(int bmpWidth, int bmpHeight) {
  if (bmpWidth_ == bmpWidth && bmpHeight == bmpHeight_) {
    return false;
  }

  if (bitmap_) {
    ::DeleteObject(bitmap_);
  }

  bmpWidth_ = bmpWidth;
  bmpHeight_= bmpHeight;

  BITMAPINFOHEADER bitmapInfo;

  bitmapInfo.biSize          = sizeof(BITMAPINFOHEADER);
  bitmapInfo.biWidth         = bmpWidth_;
  bitmapInfo.biHeight        = bmpHeight_;
  bitmapInfo.biPlanes        = 1;
  bitmapInfo.biBitCount      = 24;
  bitmapInfo.biCompression   = BI_RGB;
  bitmapInfo.biSizeImage     = 0;
  bitmapInfo.biXPelsPerMeter = 0;
  bitmapInfo.biYPelsPerMeter = 0;
  bitmapInfo.biClrUsed       = 0;
  bitmapInfo.biClrImportant  = 0;

  bitmap_ = ::CreateDIBSection(
      ::GetWindowDC(0), 
      (LPBITMAPINFO)&bitmapInfo,
      DIB_RGB_COLORS,
      (LPVOID*) &theBits_,
      0,
      0);


  if (!bitmap_) {
    ::MessageBox(0, Win32_LastError().c_str(), "CreateDIBSection failed", 0);
  }

  lineLength_ = 3*bmpWidth;
  lineLength_ = ((lineLength_ + 3) >> 2 ) << 2;

  return true;
}

DibSection::~DibSection() {
  ::DeleteObject(bitmap_);
  bitmap_=0;
}

void DibSection::BitBltTo(const DC& dcTo, int xTo, int yTo) {
  MemoryDC memDc;

  Bitmap oldBitmap = memDc.Select(*this);

  ::BitBlt (dcTo, xTo, yTo, bmpWidth_, bmpHeight_, memDc, 0, 0, SRCCOPY);

  memDc.Select(oldBitmap);
}

void DibSection::BitBltFrom(const DC& dcFrom, int xTo, int yTo, int width, int height) {
  MemoryDC memDc;

  Bitmap oldBitmap = memDc.Select(*this);

  ::BitBlt (memDc, xTo, yTo, width, height, dcFrom, 0, 0, SRCCOPY);

  memDc.Select(oldBitmap);
}


