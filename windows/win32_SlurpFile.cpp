/* 
   win32_SlurpFile.cpp

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


//      Prevent error: 'file_size' was not declared in this scope
#define _WIN32_WINNT 0x0501

#include "Win32_SlurpFile.h"

#include <windows.h>
#include <iostream>

std::string Win32_SlurpFile(std::string const& file_name) {
  HANDLE h = ::CreateFile(
    file_name.c_str(), 
    GENERIC_READ, 
    FILE_SHARE_READ, 
    0,  // security attributes
    OPEN_EXISTING,
    0,  // file attributes 
    0);

  if (!h) return "file does not exist";

  LARGE_INTEGER file_size;
  ::GetFileSizeEx(h, &file_size);
  if (file_size.HighPart) return "File way too big";

  std::string ret;

  ret.resize(file_size.LowPart+1);

  DWORD bytes_read;

  ::ReadFile(h, const_cast<void*> (reinterpret_cast<const void*>(ret.c_str())), file_size.LowPart, &bytes_read, 0);

  if (bytes_read != file_size.LowPart) std::cout << "Win32_SlurpFile: wrong number of bytes read";

  ret[file_size.LowPart] = 0;

  return ret;
}
