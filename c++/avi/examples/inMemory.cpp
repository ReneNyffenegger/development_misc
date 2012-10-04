/* 
   inMemory.cpp

   g++ -I.. -I../../../windows/w -I../../../windows    ../avi.cpp inMemory.cpp ../../../windows/w/DibSection.cpp ../../../windows/w/MemoryDC.cpp  ../../../windows/w/bitmap.cpp ../../../windows/w/DC.cpp ../../../windows/w/Color.cpp  ../../../windows/w/Font.cpp  ../../../windows/Win32_LastError.cpp -o inMemory.exe -lvfw32 -lgdi32

   An example on how to use Avi.cpp

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

#include <windows.h>
#include "avi.h"

#include <iostream>
#include <sstream>

#include "MemoryDC.h"
#include "DibSection.h"
#include "Color.h"
#include "Font.h"

int main() {
  const float frames_per_second = 24.0;

  Avi a("InMemory.avi",static_cast<int>(1000.0/frames_per_second),0);

  MemoryDC memory_dc;

  for (int i=0; i<5*frames_per_second; i++) {  
    DibSection dib_section(200, 200);
    memory_dc.Select(dib_section);
     // Set up compression just before the first frame 
     if (i==0) { 
       //AVICOMPRESSOPTIONS opts; 
       //ZeroMemory(&opts,sizeof(opts));
       //opts.fccHandler=mmioFOURCC('d','i','v','x');
       //SetAviVideoCompression(hbm,0/*&opts*/,true,0);
       HRESULT r = a.compression(dib_section, 0 /*&opts*/, true, 0);
       char buf [200];
       if (r != S_OK) {
         FormatAviMessage(r, buf, 200);
         std::cout << "compression: " << buf << std::endl;
         return -1;
       }
    }

    memory_dc.DrawOpaque(false);
    memory_dc.TextColor(Color(0,0,255));
    memory_dc.Select(Font("Arial", 100));
 
    STD_SSTR s;
    s<<i;
    memory_dc.Text(50,50,s.str().c_str());

    HRESULT r =a.add_frame(dib_section);

    char buf [200];
    if (r != S_OK) {
      FormatAviMessage(r, buf, 200);
      std::cout << buf << std::endl;
    }
  }
}
