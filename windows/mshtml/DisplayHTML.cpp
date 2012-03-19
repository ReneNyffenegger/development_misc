#include <windows.h>
#include "HTMLWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

  if (__argc < 2) {
    ::MessageBox(0, "DisplayHTML.exe html-document", "Specify HTML document to be displayed", 0);
    return -1;
  }

  HTMLWindow* html_window = new HTMLWindow (
    __argv[1],
       "DisplayHTML", 
       hInstance,
       true  // it is an url 
     );

  MSG msg;
  while (GetMessage(&msg, 0, 0, 0)) {
    TranslateMessage(&msg);
    if (msg.message >= WM_KEYFIRST && 
        msg.message <= WM_KEYLAST) {
      ::SendMessage(html_window->hwnd_, msg.message, msg.wParam, msg.lParam);
    }
    DispatchMessage(&msg);
  }

  return 0;
}
