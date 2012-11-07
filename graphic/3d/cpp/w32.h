#include <windows.h>

void W32_RegisterWindow(WNDPROC WindowProc, const char* className = "3DClass") {

  WNDCLASSEX windowClass;

  windowClass.cbSize              = sizeof(WNDCLASSEX);
  windowClass.style               = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc         = WindowProc;
  windowClass.cbClsExtra          = 0;
  windowClass.cbWndExtra          = 0;
  windowClass.hInstance           = 0;
  windowClass.hIcon               = LoadIcon  (NULL, IDI_APPLICATION);
  windowClass.hCursor             = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground       = (HBRUSH) GetStockObject(BLACK_BRUSH);
  windowClass.lpszMenuName        = NULL;
  windowClass.lpszClassName       = className;
  windowClass.hIconSm             = LoadIcon(NULL, IDI_WINLOGO);

  RegisterClassEx(&windowClass);

}

RECT W32_AdjustWindowRectEx(int width, int height, DWORD dwStyle, DWORD dwExStyle) {
  
  RECT    windowRect = {0, 0, width, height};

  AdjustWindowRectEx(
    &windowRect, 
    dwStyle, 
    FALSE,  // <-- Menu
    dwExStyle
  );

  return windowRect;
};


HWND W32_CreateWindow(int x, int y, int width, int height, const char* className = "3DClass") {
  
  DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD dwStyle   = // WS_CLIPCHILDREN | 
                    // WS_CLIPSIBLINGS | 
                    // WS_SIZEBOX      |
                    // WS_CAPTION      | 
                       WS_SYSMENU      | // show "x" in top right corner to close window.
                       WS_OVERLAPPEDWINDOW ;

  RECT rect = W32_AdjustWindowRectEx(width, height, dwStyle, dwExStyle);

  HWND hWnd = CreateWindowEx(
                 dwExStyle,
                 className,
                "TODO: App Name",
                 dwStyle,
                 0, 0,                         // x and y coords
                 rect.right  - rect.left,      // width
                 rect.bottom - rect.top,       // height
                 NULL,
                 NULL,
                 0,                            // hInstance
                 NULL);                        // no xtra params

  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);

  return hWnd;
}

int W32_EnterMessageLoop() {

  MSG        Msg;
	while( GetMessage(&Msg, NULL, 0, 0) ) {
             TranslateMessage(&Msg);
             DispatchMessage(&Msg);
	}

	return Msg.wParam;

}

HANDLE W32_CreateThread(LPTHREAD_START_ROUTINE func, LPVOID params = 0) {

    DWORD threadId;
    return            ::CreateThread(
      0,              // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
      0,              // DWORD dwStackSize,                         // initial thread stack size
      func,           // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
      params,         // LPVOID lpParameter,                        // argument for new thread
      0,              // DWORD dwCreationFlags,                     // creation flags
     &threadId        // LPDWORD lpThreadId                         // pointer to receive thread ID
    );
}
