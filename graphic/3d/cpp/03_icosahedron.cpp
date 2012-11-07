//#include <windows.h>

#include <string>

#include "w32.h"
#include "FlickerFree.h"

#include "point3d.h"
#include "point2d.h"

#include "matrix.h"

#include "3d.h"

#include "Mesh.h"

#include <stdio.h>

//#include "DrawIcosahedron.h"





// Distance of eyes from screen (in Centimeters)
// const double distanceFromScreenCm = 60;

// Distance of eyes above 0/0 coordinates (in Centimeters)
// const double distanceAboveCenterCm = 0;

// Distance of eyes right of 0/0 coordinates (in Centimeters)
// const double distanceRightOfCenterCm = 0;

// Distance of left eye from right eye
// const double distanceEyesCm = 6.8;

//const point3d left_eye  = point3d(distanceRightOfCenterCm - distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);
//const point3d right_eye = point3d(distanceRightOfCenterCm + distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);






//void DrawCube(HDC dc, matrix_4 const& matrix,  point3d left_eye, point3d right_eye, double length_edge) {
//
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2, -length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d(-length_edge/2,  length_edge/2, -length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2,  length_edge/2, -length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2, -length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2,  length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2,  length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2, -length_edge/2), point3d(-length_edge/2,  length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2,  length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
//     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2,  length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 
//
//}

LRESULT CALLBACK WindowProc(
             HWND    hWnd, 
             UINT   Msg,
			       WPARAM wParam, 
             LPARAM lParam)
{
    switch(Msg) {


    case WM_DESTROY: // Sent when a window is being destroyed.
         PostQuitMessage(/* nExitCode: */ 0 /*WM_QUIT*/);
         // MSDN: If an application processes this message, 
         // it should return zero:
         return 0;


    default:
        // Process the left-over messages
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
}

DWORD WINAPI Timer(LPVOID p) {

  HWND hWnd = (HWND) *((HWND*) p);
  HDC  dc   = ::GetDC(hWnd);


  Mesh mesh_icosahedron = CreateIcosahedronMesh(5);

  while (1) {
//   ::Sleep((int) (1000/ 25/*framesPerSecond*/));
     //::InvalidateRect(hWnd, 0 /*null*/, FALSE);

      static double r = 0;

    
      r = r + 1.0/100.0;
    
//    if (r > 20) {
 //     ::MessageBox(0, "r", "",0);
//      r=0;
//    }
    
      matrix_4 rot;
      matrix_4 trans;
    
    
//    rot.rotation_x(r /*2.0 * */ /*3.14159265358979323846*/);
//    rot.rotation(std::pow(1.0, 1/3),std::pow(1.0, 1/3), std::pow(1.0,1/3), r);
//    rot.rotation(std::sqrt(2.0)/2.0,std::sqrt(2.0)/2.0,               0.0, r);
      rot.rotation(              1.0 ,               4.0,               1.0, r);
    
    //rot.translation(7, -2, r);
      trans.translation(0, 0, -10) ;
    //trans.translation(0, 0,  0) ;
    
      matrix_4 final_ = trans * rot * trans;
//    matrix_4 final_ = trans;
    //matrix_4 final_;
    


    // Matrix Adjusted ------------------------ }


    // TODO!
     RECT windowRect = {0, 0, windowWidth, windowHeight};



//       ::SetROP2(flickerFreeMemoryDc/*dcMemory*/, R2_BLACK);
         ::FillRect (flickerFreeMemoryDc/*dcMemory*/, &windowRect, (HBRUSH) :: GetStockObject(BLACK_BRUSH));

         ::SetROP2(flickerFreeMemoryDc/*dcMemory*/, R2_MERGEPEN);
         Viewer viewer;
//       DrawCube(flickerFreeMemoryDc/*dcMemory*/, final_, viewer/*left_eye, right_eye*/*/*/*/*/*/*/*/*/, 4);
         DrawMesh(flickerFreeMemoryDc/*dcMemory*/, final_, mesh_icosahedron, viewer/*left_eye, right_eye*/, 4);

         // }

         // -------------- Measure fps {

         static DWORD tickCount_at_MeasureStart = ::GetTickCount();
         static int   frame_counter = 0;

         frame_counter++;

         DWORD tickCount_now     = ::GetTickCount();


         static char buffer[100];
//       sprintf(buffer, "mSecs: %d", mSecs);


         int tickCount_since_MeasureStart  = tickCount_now - tickCount_at_MeasureStart;
         if (tickCount_since_MeasureStart > 1000) {
           sprintf (buffer, "fps: %d", frame_counter);
           frame_counter = 0;
           tickCount_at_MeasureStart = tickCount_now;
         }
         ::TextOut(flickerFreeMemoryDc/*dcMemory*/, 0, 0, buffer, strlen(buffer));
//       ::TextOut(dc                 /*dcMemory*/, 0, 0, buffer, strlen(buffer));


         // --------------- fps Measured }


         ::BitBlt ( dc, 
                            0, 0, windowWidth, windowHeight,
                            flickerFreeMemoryDc/*dcMemory*/,
                            0, 0,
                            SRCCOPY
                          );

         // Flicker Free: Part II {
//       win32_api SelectObject(dcMemory, hOldBitmap);
//       win32_api DeleteDC(dcMemory);
//       win32_api DeleteObject(PersistenceBitmap);



  }
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {


  
  W32_RegisterWindow(WindowProc);

  HWND hWnd = W32_CreateWindow(0, 0, windowWidth, windowHeight);

  InitFlickerFree(hWnd, windowWidth, windowHeight);


  // { Thread
  DWORD threadId;
  HANDLE hTimer  =  ::CreateThread(
    0,              // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
    0,              // DWORD dwStackSize,                         // initial thread stack size
    Timer,          // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
   (LPVOID) &hWnd,  // LPVOID lpParameter,                        // argument for new thread
    0,              // DWORD dwCreationFlags,                     // creation flags
   &threadId        // LPDWORD lpThreadId                         // pointer to receive thread ID
  );
  // }


  return W32_EnterMessageLoop();
}
