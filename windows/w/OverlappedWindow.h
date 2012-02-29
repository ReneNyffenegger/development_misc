/* 
   OverlappedWindow.h

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

#ifndef OVERLAPPED_WINDOW_H_
#define OVERLAPPED_WINDOW_H__

#include <windows.h>

#include <string>

#include "Wnd.h"

class OverlappedWindow : public Wnd {
public:
  OverlappedWindow(
    WNDPROC WndProc,
    STD_STR const& title,
    int   x = CW_USEDEFAULT,
    int   y = CW_USEDEFAULT,
    int   w = CW_USEDEFAULT,
    int   h = CW_USEDEFAULT,
    int    windowStyles = 0);

  virtual Wnd* Parent() const { return 0;};

  virtual int  StylesToAddInCreate() const {return WS_OVERLAPPEDWINDOW;};
};

#endif

