#include <windows.h>

#include <string>
#include "point3d.h"
#include "point2d.h"

#include "matrix.h"


const COLORREF color_for_right_eye   = RGB(255,   0,   0);
const COLORREF color_for_left_eye    = RGB(  0, 204, 255); //RGB(  0, 0, 255);

const int windowWidth  = 1000;
const int windowHeight = 1000;

const double pixelPerCmHorizontal = 1000/26.8;
const double pixelPerCmVertical   = 1000/26.1;

// Distance of eyes from screen (in Centimeters)
const double distanceFromScreenCm = 60;

// Distance of eyes above 0/0 coordinates (in Centimeters)
const double distanceAboveCenterCm = 10;

// Distance of eyes right of 0/0 coordinates (in Centimeters)
const double distanceRightOfCenterCm = 10;

// Distance of left eye from right eye
const double distanceEyesCm = 6.8;

const point3d left_eye  = point3d(distanceRightOfCenterCm - distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);
const point3d right_eye = point3d(distanceRightOfCenterCm + distanceEyesCm/2, distanceAboveCenterCm, distanceFromScreenCm);


point2d MapPointOntoScreen(point3d const& eye, point3d const& point) {

  point2d point_;

  point_.x = (point.x - eye.x) / (eye.z - point.z) * eye.z + eye.x;
  point_.y = (point.y - eye.y) / (eye.z - point.z) * eye.z + eye.y;

  return point_;
}



void DrawLine (

     HDC dc,
     point3d const& eye,
     point3d const& from,
     point3d const& to

) {

  matrix_4 rot;
  matrix_4 trans;


  rot.rotation_x(M_PI/5);
  trans.translation(- 7,2,-30);

  matrix_4 final_ = trans * rot;

  vector_4 vector_from(from.x, from.y, from.z, 1);
  vector_4 vector_to__(to  .x, to  .y, to  .z, 1);

  vector_4 vector_from_translated = final_ * vector_from;
  vector_4 vector_to___translated = final_ * vector_to__;

 
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
     point3d const& eye_left,
     point3d const& eye_right,
     point3d const& from,
     point3d const& to

) {

  HPEN pen_for_left_eye = CreatePen(PS_SOLID, 1, color_for_left_eye);
  HPEN pen_old          =(HPEN) SelectObject(dc, pen_for_left_eye);

  DrawLine(dc, eye_left, from, to);

  HPEN pen_for_right_eye = CreatePen(PS_SOLID, 1, color_for_right_eye);
  SelectObject(dc, pen_for_right_eye);

  DrawLine(dc, eye_right, from, to);

  SelectObject(dc, pen_old);

  DeleteObject(    pen_for_right_eye);
  DeleteObject(    pen_for_left_eye );
}

LRESULT CALLBACK WindowProc(
             HWND    hWnd, 
             UINT   Msg,
			       WPARAM wParam, 
             LPARAM lParam)
{
    switch(Msg) {

    case WM_PAINT: {
         // Request to paint

         PAINTSTRUCT ps;
	       HDC dc = BeginPaint(hWnd, &ps);

         SetROP2(dc, R2_MERGEPEN);


         DrawLine(dc, left_eye, right_eye, point3d(-4, -4, -4), point3d( 4, -4, -4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4, -4, -4), point3d(-4,  4, -4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4, -4, -4), point3d(-4, -4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4,  4, -4), point3d( 4,  4, -4)); 
         DrawLine(dc, left_eye, right_eye, point3d( 4,  4, -4), point3d( 4, -4, -4)); 
         DrawLine(dc, left_eye, right_eye, point3d( 4, -4, -4), point3d( 4, -4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d( 4, -4,  4), point3d(-4, -4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d( 4, -4,  4), point3d( 4,  4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d( 4,  4, -4), point3d( 4,  4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4,  4, -4), point3d(-4,  4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4,  4,  4), point3d( 4,  4,  4)); 
         DrawLine(dc, left_eye, right_eye, point3d(-4,  4,  4), point3d(-4, -4,  4)); 

		     EndPaint  (hWnd, &ps);
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

  RECT    windowRect = {0, 0, windowWidth, windowHeight};
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

  MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) ) {

            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
