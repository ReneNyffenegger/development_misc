/* 
   OverlappedWindow.cpp

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

#include "OverlappedWindow.h"

OverlappedWindow::OverlappedWindow(
    WNDPROC WndProc,
    STD_STR const& title,
    int    x,
    int    y,
    int    w,
    int    h,
    int    windowStyles
    ) {

  WNDCLASSEX wce;

  wce.cbSize        = sizeof(wce);
  wce.style         = CS_VREDRAW | CS_HREDRAW; 
  wce.lpfnWndProc   = WndProc; 
  wce.cbClsExtra    = 0; 
  wce.cbWndExtra    = 0; 
  wce.hInstance     = 0; 
  wce.hIcon         = LoadIcon(0, IDI_APPLICATION); 
  wce.hCursor       = LoadCursor(0, IDC_ARROW); 
  wce.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
  wce.lpszMenuName  = 0;
  wce.lpszClassName = "DummyClassName",
  wce.hIconSm       = 0;

  if (!RegisterClassEx(&wce)) throw "Couldn not register class";

  Create("DummyClassName", x, y, w, h, windowStyles, title);
};

