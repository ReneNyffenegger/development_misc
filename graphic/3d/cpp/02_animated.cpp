#include <windows.h>

#include <string>
#include "point3d.h"
#include "point2d.h"

#include "matrix.h"

#include <stdio.h>

// Flicker Free Pre-Part {
HBITMAP PersistenceBitmap;
HDC     dcMemory;
// Flicker Free }


const COLORREF color_for_right_eye = RGB(255,   0,   0);
const COLORREF color_for_left_eye  = RGB(  0,   0, 255); // RGB(  0, 204, 255);

const int windowWidth  = 1000;
const int windowHeight = 1000;

RECT    windowRect = {0, 0, windowWidth, windowHeight};

const double pixelPerCmHorizontal = 1000/26.8;
const double pixelPerCmVertical   = 1000/26.1;

// Distance of eyes from screen (in Centimeters)
const double distanceFromScreenCm = 60;

// Distance of eyes above 0/0 coordinates (in Centimeters)
const double distanceAboveCenterCm = 0;

// Distance of eyes right of 0/0 coordinates (in Centimeters)
const double distanceRightOfCenterCm = 0;

// Distance of left eye from right eye
const double distanceEyesCm = 6.8;

const point3d left_eye  = point3d(distanceRightOfCenterCm - distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);
const point3d right_eye = point3d(distanceRightOfCenterCm + distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);


const double framesPerSecond = 50;

point2d MapPointOntoScreen(point3d const& eye, point3d const& point) {

  point2d point_;

  point_.x = (point.x - eye.x) / (eye.z - point.z) * eye.z + eye.x;
  point_.y = (point.y - eye.y) / (eye.z - point.z) * eye.z + eye.y;

  return point_;
}



void DrawLine (

     HDC dc,
     matrix_4  const& matrix,
     point3d   const& eye,
     point3d   const& from,
     point3d   const& to

) {


  vector_4 vector_from(from.x, from.y, from.z, 1);
  vector_4 vector_to__(to  .x, to  .y, to  .z, 1);

  vector_4 vector_from_translated = matrix * vector_from;
  vector_4 vector_to___translated = matrix * vector_to__;

 
  point3d from_translated = vector_from_translated.make_point_3d();
  point3d to_translated   = vector_to___translated.make_point_3d();

  point2d from_ = MapPointOntoScreen(eye, from_translated);
  point2d to_   = MapPointOntoScreen(eye, to_translated );

  MoveToEx(
    dc, 
    (int) (windowWidth /2 + from_.x * pixelPerCmVertical  ),
    (int) (windowHeight/2 - from_.y * pixelPerCmHorizontal),
    0);

  LineTo(
    dc, 
    (int) (windowWidth /2 + to_.x * pixelPerCmVertical  ),
    (int) (windowHeight/2 - to_.y * pixelPerCmHorizontal));

}

void DrawLine (

     HDC dc,
     matrix_4 const& matrix,
     point3d const& eye_left,
     point3d const& eye_right,
     point3d const& from,
     point3d const& to

) {

  HPEN pen_for_left_eye = CreatePen(PS_SOLID, 1, color_for_left_eye);
  HPEN pen_old          =(HPEN) SelectObject(dc, pen_for_left_eye);

  DrawLine(dc, matrix, eye_left, from, to);

  HPEN pen_for_right_eye = CreatePen(PS_SOLID, 1, color_for_right_eye);
  SelectObject(dc, pen_for_right_eye);

  DrawLine(dc, matrix, eye_right, from, to);

  SelectObject(dc, pen_old);

  DeleteObject(    pen_for_right_eye);
  DeleteObject(    pen_for_left_eye );
}


void DrawCube(HDC dc, matrix_4 const& matrix,  point3d left_eye, point3d right_eye, double length_edge) {

     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2, -length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d(-length_edge/2,  length_edge/2, -length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2, -length_edge/2, -length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2,  length_edge/2, -length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2, -length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2, -length_edge/2), point3d( length_edge/2, -length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2,  length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2, -length_edge/2,  length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d( length_edge/2,  length_edge/2, -length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2, -length_edge/2), point3d(-length_edge/2,  length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2,  length_edge/2), point3d( length_edge/2,  length_edge/2,  length_edge/2)); 
     DrawLine(dc, matrix, left_eye, right_eye, point3d(-length_edge/2,  length_edge/2,  length_edge/2), point3d(-length_edge/2, -length_edge/2,  length_edge/2)); 

}

LRESULT CALLBACK WindowProc(
             HWND    hWnd, 
             UINT   Msg,
			       WPARAM wParam, 
             LPARAM lParam)
{
    switch(Msg) {


    case WM_CREATE: {

         // Flicker Free {
         HDC dc = ::GetDC(hWnd);
         PersistenceBitmap = CreateCompatibleBitmap(dc,windowWidth,windowHeight);
       /*HDC*/   dcMemory = ::CreateCompatibleDC(dc);
         HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(dcMemory, PersistenceBitmap);

//       should probably be done when Window is resized:
//       ::SelectObject(dcMemory, hOldBitmap);
//       ::DeleteDC(dcMemory);
//       ::DeleteObject(PersistenceBitmap);
         
         // Flicker Free }

         // returning 0 indicates that it should be continued creating the window.
         return 0; 

    }
    case WM_PAINT: {

      // Adjust Matrix ---------------------- {

      static double r = 0;
    
      r = r + 1.0/1000.0;
    
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

      PAINTSTRUCT ps;

	    HDC dc = BeginPaint(hWnd, &ps);

      // Flicker Free: Part I {

      ::FillRect (dcMemory, &windowRect, (HBRUSH) ::GetStockObject(BLACK_BRUSH));

      ::SetROP2(dcMemory, R2_MERGEPEN);
      DrawCube(dcMemory, final_, left_eye, right_eye, 4);

      // }

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
      TextOut(dcMemory, 0, 0, buffer, strlen(buffer));


      // --------------- fps Measured }


      ::BitBlt ( dc, 
                 0, 0, windowWidth, windowHeight,
                 dcMemory,
                 0, 0,
                 SRCCOPY
               );

		  ::EndPaint(hWnd, &ps);
      ::InvalidateRect(hWnd, 0, FALSE);

      return 0;
    }
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


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {

  char const * const className = "3DClass";


  WNDCLASSEX 
       windowClass;
       windowClass.cbSize              = sizeof(WNDCLASSEX);
       windowClass.style               = CS_HREDRAW | CS_VREDRAW;
       windowClass.lpfnWndProc         = WindowProc;
       windowClass.cbClsExtra          = 0;
       windowClass.cbWndExtra          = 0;
       windowClass.hInstance           = hInstance;
       windowClass.hIcon               = LoadIcon  (NULL, IDI_APPLICATION);
       windowClass.hCursor             = LoadCursor(NULL, IDC_ARROW);
       windowClass.hbrBackground       = (HBRUSH) GetStockObject(BLACK_BRUSH);
       windowClass.lpszMenuName        = NULL;
       windowClass.lpszClassName       = className;
       windowClass.hIconSm             = LoadIcon(NULL, IDI_WINLOGO);

  RegisterClassEx(&windowClass);

  DWORD   dwExStyle;
  DWORD   dwStyle;

  dwStyle   = // WS_CLIPCHILDREN | 
              // WS_CLIPSIBLINGS | 
              // WS_SIZEBOX      |
              // WS_CAPTION      | 
                 WS_SYSMENU      | // show "x" in top right corner to close window.
                 WS_OVERLAPPED ;

  dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  HWND hwnd = CreateWindowEx(
                 dwExStyle,
                 className,
                "TODO: App Name",
                 dwStyle,
                 0, 0,                               // x and y coords
                 windowRect.right - windowRect.left,
                 windowRect.bottom - windowRect.top, // width, height
                 NULL,                               // handle to parent
                 NULL,                               // handle to menu
                 hInstance,                          // application instance
                 NULL);                              // no xtra params

  if (! hwnd) {
    MessageBox(0, "Main window could not be created", "Error", 0);
    return 0;
  }

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);


  MSG        Msg;
	while( GetMessage(&Msg, NULL, 0, 0) ) {
             TranslateMessage(&Msg);
             DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

