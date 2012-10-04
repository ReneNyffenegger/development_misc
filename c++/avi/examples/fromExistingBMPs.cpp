

/* 
   fromExistingBMPs.cpp

   g++ -I.. -I../../../windows/w -I../../../windows    ../avi.cpp fromExistingBMPs.cpp ../../../windows/w/bitmap.cpp ../../../windows/Win32_LastError.cpp -o fromExistingBMPs.avi  -lvfw32 -lgdi32


   An example on how to use avi.cpp

   Copyright (c) 2004 René Nyffenegger 

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
#include "Avi.h"

#include <iostream>

#include "Bitmap.h"

int main() {
  const char *fns[] = {"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp"};

  Avi avi("fromExistingBMPs.avi", 1000, 0); // 1000ms is the period between frames

  for (unsigned int i=0; i<sizeof(fns)/sizeof(fns[0]); i++) {  
    Bitmap bmp(fns[i]);

    // Use the AVICOMPRESSOPTIONS struct to set up compression (before shooting the first frame)
    // Pass a zero to use the default.
    if (i==0) { 
      //AVICOMPRESSOPTIONS opts; 
      //ZeroMemory(&opts,sizeof(opts));
      //opts.fccHandler=mmioFOURCC('d','i','v','x');
      avi.compression(bmp, 0 /*&opts*/, true, 0);
    }

    if (avi.add_frame(bmp) != S_OK) {
      std::cout << "Could not add frame" << std::endl;
      return -1;
    }
    ::DeleteObject(bmp);
  }
  //AddAviWav(avi,"wav.wav",SND_FILENAME);
  //avi.add_wav("wav.wav",SND_FILENAME);
  //CloseAvi(avi);
}

