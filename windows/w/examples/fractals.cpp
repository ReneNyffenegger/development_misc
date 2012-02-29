/* 
   Fractals.cpp

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

   --

   Compiling with MinGW:
   ---------------------

     
      g++ -mwindows -I.. -I../.. fractals.cpp ../PaintDC.cpp ../DibSection.cpp ../Wnd.cpp ../MemoryDC.cpp ../DC.cpp ../OverlappedWindow.cpp ../Bitmap.cpp ../Color.cpp ../WndApplication.cpp ../../win32_LastError.cpp  -ofractals.exe

*/

#include <process.h>
#include <complex>

#include "OverlappedWindow.h"
#include "PaintDC.h"
#include "Color.h"
#include "DibSection.h"

#include "WndApplication.h"

int fractalWidth = 500;
int fractalHeight= 500;
int nofIterations= 255;

unsigned int* palette;

DibSection dibsection;

LRESULT CALLBACK WndProc(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam ) {

  switch( msg ) {
    case WM_PAINT: {
      PaintDC pdc(hWnd);
      dibsection.BitBltTo(pdc,0,0);
    }
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
      return DefWindowProc( hWnd, msg, wParam, lParam);
  } 
  return 0;
}

unsigned __stdcall DoFractal(void* v) {
  for (int y=0; y<fractalHeight; y++) {
    for (int x=0; x<fractalWidth; x++) {
      int iter=0;
      std::complex<float> z(0,0);
      std::complex<float> c(
            2.0*(x-fractalWidth/ 2)/fractalWidth ,
            2.0*(y-fractalHeight/2)/fractalHeight
          );

      while (iter<nofIterations) {
        z=z*z+c;
        if (abs(z) > 2) break;
        iter++;
      }
      dibsection.PixelAt(x,y,palette[iter]);
    }
  }

  return 0;
}


unsigned __stdcall Invalidater(void* v) {
  OverlappedWindow* ov = reinterpret_cast<OverlappedWindow*>(v);
  while (1) {
    ov->Refresh();
    Sleep(1000);
  }
  return 0;
}

int WINAPI WinMain(
             HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow) {

  palette = new unsigned int[nofIterations];
  for (int c=0; c<nofIterations; c++) {
    palette[c] = c + c*256 + c*256*256;
  }

  dibsection.Size(fractalWidth, fractalHeight);

  RECT rect;
  rect.bottom=fractalHeight;
  rect.left  =0;
  rect.right =fractalWidth;
  rect.top   =0;
  AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

  int adjWidth = rect.right  - rect.left;
  int adjHeight= rect.bottom - rect.top;

  OverlappedWindow ow(WndProc, "Fractals", 50, 100, adjWidth, adjHeight, 0);

  ow.Show();

  _beginthreadex(0,0,Invalidater,reinterpret_cast<void*>(&ow),0,0);
  _beginthreadex(0,0,DoFractal  ,0                           ,0,0);

  return EnterMsgLoop();
}
