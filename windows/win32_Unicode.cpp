/* 
   win32_Unicode.cpp

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

#include "win32_Unicode.h"
#include <windows.h>

std::string ws2s(std::wstring const& s) {

  int lengthOfStr = ::WideCharToMultiByte(
    CP_ACP,
    0,
    s.c_str(),
   -1,  // number of chars in string. -1 indicates that string is 0 terminated
    0,
    0,
    0,
    0);


  char* r=new char[lengthOfStr];

  ::WideCharToMultiByte(
    CP_ACP,
    0,
    s.c_str(),
   -1,
    r,
    lengthOfStr,
    0,
    0);

  std::string ret=r;
  delete [] r;

  return ret;
}

std::wstring s2ws(std::string const& s, unsigned int codepage) {

#ifdef _DEBUG
  if (codepage != CP_ACP) {
  if (! ::IsValidCodePage(codepage))
    throw "Invalid codepage given to stdStringToStdWstring";
  } 
#endif

  int lengthOfWStr = ::MultiByteToWideChar(
      //CP_ACP,
      codepage,
      //0,
      MB_PRECOMPOSED,
      s.c_str(),
     -1,
     0,
     0);


  wchar_t* r=new wchar_t[lengthOfWStr];

  ::MultiByteToWideChar(
      codepage,
      //0,
      MB_PRECOMPOSED,
      s.c_str(),
     -1,
      r,
      lengthOfWStr);

  std::wstring ret=r;
  delete [] r;

  return ret;
}
