/* 
   Wnd.cpp

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

#include "Wnd.h"

#include <windows.h>

Wnd::Wnd() : hwnd_(0) {
}

Wnd::~Wnd() {
}

void Wnd::Create(STD_STR const& className, int x, int y, int w, int h, int styles, STD_STR const& title) {
  Wnd* parent = Parent();
  HWND hparent = parent ? parent->hwnd_ : 0;

  styles |= StylesToAddInCreate();

  HMENU hmenu = (HMENU) (hparent ? 1 : 0);

  hwnd_ = ::CreateWindowEx(
    0,                // Ex Styles
    className.c_str(),
    title.c_str(),
    styles,
    x, y, w, h,
    hparent,        
    hmenu,      // Menu, or windows id if child
    0,       
    0           // Pointer to window specific data
  );

  ::SetWindowLong(hwnd_,GWL_USERDATA,(LONG) this);
}

void Wnd::ClientRect(unsigned int& width, unsigned int& height) const {
  RECT r;

  ::GetClientRect(hwnd_, &r);
  width  = r.right;
  height = r.bottom;
}

void Wnd::Show(bool b) const {
  if (b) ::ShowWindow(hwnd_, SW_SHOW);
  else   ::ShowWindow(hwnd_, SW_HIDE);
}

void Wnd::Enable(bool b) const {
  ::EnableWindow(hwnd_, b);
}

void Wnd::Focus() const {
  ::SetFocus(hwnd_);
}

void Wnd::DefaultGuiFont() {
  ::SendMessage(hwnd_,WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);
}

void Wnd::Refresh() const {
  ::InvalidateRect(hwnd_, 0, 1);
}

void Wnd::Text(const STD_STR& t) {
  ::SetWindowText(hwnd_, t.c_str());
}

STD_STR Wnd::Text() const {
  int textLength = ::GetWindowTextLength(hwnd_) + 1;
  //wchar_t *t = new wchar_t[textLength];
  TCHAR* t = new TCHAR[textLength];
  ::GetWindowText(hwnd_, t, textLength);
  STD_STR ret(t);
  delete [] t;
  return ret;
}

void Wnd::Move(int x, int y, int width, int height, bool repaint) {
  ::MoveWindow(hwnd_,x,y,width,height,repaint);
}
