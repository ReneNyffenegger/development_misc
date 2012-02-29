/* 
   File DC.cpp: Copyright (C) René Nyffenegger

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


#include "DC.h"
#include "Color.h"
#include "Font.h"
#include "Pen.h"

#include <sstream>

DC::DC(HDC dc) : dc_(dc) {}

DC::~DC() {}

void DC::Text(int x, int y, const STD_STR& text) {
  ::TextOut(dc_, x, y, text.c_str(), text.length());
}

void DC::Text(int x, int y, const STD_STR& text, const Color& color) {
  Color oldColor=TextColor();
  TextColor(color);
  ::TextOut(dc_, x, y, text.c_str(), text.length());
  TextColor(oldColor);
}

void DC::Text(int x, int y, int i) {
  STD_SSTR s;
  s << i;
  Text(x, y, s.str().c_str());
}

DC::operator HDC () const {
  return dc_;
}

void DC::BackgroundColor(unsigned char red, unsigned char green, unsigned char blue) {
  if (::SetBkColor(dc_, RGB(red, green, blue)) == CLR_INVALID) {
    throw "SetBkColor";
  }
}

void DC::DrawOpaque(bool b) {
  if (b) {
    ::SetBkMode(dc_, OPAQUE);
  }
  else {
    ::SetBkMode(dc_, TRANSPARENT);
  }
}

void DC::Line(int xTo, int yTo) {
  ::LineTo(dc_, xTo, yTo);
}

void DC::Move(int x, int y) {
  ::MoveToEx(dc_, x, y, 0);
}

Pen DC::Select(Pen& pen) {
  return Pen(static_cast<HPEN>(::SelectObject(dc_, pen)));
}

Font DC::Select(Font const& font) {
  return Font(static_cast<HFONT>(::SelectObject(dc_, font)));
}

void DC::TextAlign(v_textalignment va, h_textalignment ha) {
  ::SetTextAlign(dc_, va | ha);
}

void DC::TextColor(const Color& color) {
  ::SetTextColor(dc_, color.color_);
}

Color DC::TextColor() const {
  return Color(::GetTextColor(dc_));
}
