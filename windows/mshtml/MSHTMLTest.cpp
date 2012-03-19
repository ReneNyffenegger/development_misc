#include <windows.h>
#include "HTMLWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE /*unused__*/, LPSTR /*lpszCmdLine*/, int /*nCmdShow*/) {

  HTMLWindow* html_window = new HTMLWindow (

      // Parameter html_or_url:
      "<html><head>"
      "<title>MSHTMLTest</title>"   // seems a little useless in this context
      "</head><body>"
      "<h1>This is a test</h1>"
      "I offer the following links:"
      "<ul>"
      "<li><a href='http://www.google.com'>www.google.com</a>"
      "<li><a href='http://www.adp-gmbh.ch'>www.adp-gmbh.ch</a>"
      "<li><a href='http://www.yahoo.com'>www.yahoo.com</a>"
      "</ul>"
      "</body></html>",
      // Parameter title 
       "MSHTMLTest", 
       hInstance,
      false  // indicates: this not an url, but html 
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
