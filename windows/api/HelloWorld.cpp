//
//  Compiled with mingw: 
//
//    g++ -mwindows HelloWorld.cpp
//

#include <windows.h>

LRESULT CALLBACK WndProc(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam ) {

  switch( msg ) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint(hWnd, &ps);

      // Print "Hello World" at coordinates 10/40.
      // 11 is the length of "Hello World".
      TextOut(hDC, 10, 40, "Hello World", 11);
      EndPaint(hWnd, &ps);
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


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {

  WNDCLASSEX wce;

  wce.cbSize        = sizeof(wce);
  wce.style         = CS_VREDRAW | CS_HREDRAW; 
  wce.lpfnWndProc   = (WNDPROC) WndProc; 
  wce.cbClsExtra    = 0; 
  wce.cbWndExtra    = 0; 
  wce.hInstance     = hInstance; 
  wce.hIcon         = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
  wce.hCursor       = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
  wce.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
  wce.lpszMenuName  = 0;
  wce.lpszClassName = "HelloWorldClass",
  wce.hIconSm       = 0;
 
  if (!RegisterClassEx(&wce)) return 0; 
  
  HWND hWnd = CreateWindowEx(
     0,                   // Ex Styles
    "HelloWorldClass",
    "Hello World",        // Title
     WS_OVERLAPPEDWINDOW,
     CW_USEDEFAULT,       // x
     CW_USEDEFAULT,       // y
     CW_USEDEFAULT,       // Height
     CW_USEDEFAULT,       // Width
     NULL,                // Parent Window
     NULL,                // Menu, or windows id if child
     hInstance,           // 
     NULL                 // Pointer to window specific data
  );

  ShowWindow( hWnd, nCmdShow );

  MSG msg;
  int r;
  while ((r = GetMessage(&msg, NULL, 0, 0 )) != 0) { 
    if (r == -1) {
      ;  // Error!
    }
    else {
      TranslateMessage(&msg); 
      DispatchMessage(&msg); 
    }
  } 

  // The application's return value
  return msg.wParam;
};
