#include <cmath>
#include "w32.h"
#include "FlickerFree.h"
#include "point2d.h"
#include "point3d.h"
#include "matrix.h"
#include "3d.h"

#include "PlanetPositionsUsingEllipticalOrbits.h"

#include <stdio.h>

LRESULT CALLBACK WindowProc(
             HWND    hWnd, 
             UINT   Msg,
			       WPARAM wParam, 
             LPARAM lParam)
{
    switch(Msg) {


    case WM_DESTROY:
         PostQuitMessage(/* nExitCode: */ 0 /*WM_QUIT*/);
         // MSDN: If an application processes this message, 
         // it should return zero:
         return 0;


    default:
        // Process the left-over messages
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
}


DWORD WINAPI TimerThread(LPVOID p) {

  HWND hWnd = (HWND) *((HWND*) p);

  FlickerFreeSupport flickerFree;
  flickerFree.Init(hWnd, windowWidth, windowHeight);

  ::SetROP2(flickerFree.memoryDC, R2_MERGEPEN);

  matrix_4 trans_sun;
  matrix_4 rotate_solar_system;
  matrix_4 scale;
  trans_sun.translation(0, -0, -1);
  rotate_solar_system.rotation_x(M_PI / 2.2);
  scale.scale(4);

  Viewer viewer;

  PlanetPositionsUsingEllipticalOrbits planets;
  while (1) {

      static double julian_day;
      static double tick_count_first = ::GetTickCount();
    
      matrix_4 final_ = trans_sun;

         
      flickerFree.StartNewFrame();


      // 1 year every 10 seconds.
      julian_day = -365.0 + (::GetTickCount() -tick_count_first) / 1000.0 * 365.24 / 10.0;  

      DrawPoint(flickerFree.memoryDC, final_, viewer, point3d(0, 0, 0)                      , 1.0/4.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.mercury.positionAU(julian_day), 1.0/7.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.venus  .positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.earth  .positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.mars   .positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.jupiter.positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.saturn .positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.uranus .positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.neptune.positionAU(julian_day), 1.0/5.0);
      DrawPoint(flickerFree.memoryDC, final_, viewer, planets.pluto  .positionAU(julian_day), 1.0/5.0);

//    DrawLine (flickerFree.memoryDC, final_, viewer, planets.earth.positionAU(julian_day), point3d(0,0,0));

      // -------------- Measure fps {

      static DWORD tickCount_at_MeasureStart = ::GetTickCount();
      static int   frame_counter = 0;

      frame_counter++;

      DWORD tickCount_now     = ::GetTickCount();

      static char buffer[100];


      int tickCount_since_MeasureStart  = tickCount_now - tickCount_at_MeasureStart;
      if (tickCount_since_MeasureStart > 1000) {
        sprintf (buffer, "fps: %d", frame_counter);
        frame_counter = 0;
        tickCount_at_MeasureStart = tickCount_now;
      }
      ::TextOut(flickerFree.memoryDC, 0, 0, buffer, strlen(buffer));


      // --------------- fps Measured }

      flickerFree.BitBlt();
  }
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {


  
  W32_RegisterWindow(WindowProc);

  HWND   hWnd   = W32_CreateWindow(0, 0, windowWidth, windowHeight);
  HANDLE hTimer = W32_CreateThread(TimerThread, (LPVOID) &hWnd);

  return W32_EnterMessageLoop();
}
