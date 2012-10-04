/* 
   AviMemDC.cpp

   A C++ class for creating avi files

   Copyright (c) 2004, 2005 René Nyffenegger 

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

#include "AviMemDC.h"

AviMemDC::AviMemDC(int width, int height, std::string const& avi_file, int frames_per_second) : 
  MemoryDC(),
  dib_section_(width, height),
  avi_(avi_file, 1000/frames_per_second, 0),
  compression_chosen_(false)
{
  Select(dib_section_);
}

void AviMemDC::AddFrame() {
  if (!compression_chosen_) {
    avi_.compression(dib_section_, 0, true, 0);
    compression_chosen_ = true;
  }
  avi_.add_frame(dib_section_);
}

DibSection& AviMemDC::GetDibSection() {
  return dib_section_;
}

