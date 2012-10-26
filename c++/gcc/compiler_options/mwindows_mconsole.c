//
//  Cf https://github.com/ReneNyffenegger/development_misc/blob/master/windows/api/HelloWorld.cpp
//
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam ) {

  printf("Message: %i\n", msg);

  switch (msg) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint(hWnd, &ps);
      TextOut(hDC, 10, 40, "Test compiler flag -mwindows and -console", 41);
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


//  The following macro ENTRY is either defined to
//     o   int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//     o   int main()

ENTRY {

  WNDCLASSEX wce;

  wce.cbSize        = sizeof(wce);
  wce.style         = CS_VREDRAW | CS_HREDRAW; 
  wce.lpfnWndProc   = (WNDPROC) WndProc; 
  wce.cbClsExtra    = 0; 
  wce.cbWndExtra    = 0; 
  wce.hInstance     = 0; 
  wce.hIcon         = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
  wce.hCursor       = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
  wce.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
  wce.lpszMenuName  = 0;
  wce.lpszClassName ="HelloWorldClass",
  wce.hIconSm       = 0;
 
  if (!RegisterClassEx(&wce)) return 0; 
  
  HWND hWnd = CreateWindowEx(0, "HelloWorldClass", "Hello World",
     WS_OVERLAPPEDWINDOW,
     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
     NULL, NULL, 0, NULL
  );

  ShowWindow(hWnd, SW_SHOW);

  MSG msg;
  int r;
  while ((r = GetMessage(&msg, NULL, 0, 0)) != 0) { 
    if (r == -1) { ; /* Error */}
    else {
      TranslateMessage(&msg); 
      DispatchMessage(&msg); 
    }
  } 

  return msg.wParam;
};
