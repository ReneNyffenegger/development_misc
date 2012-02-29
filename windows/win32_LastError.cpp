/* See http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/formatmessage.asp */

#include <windows.h>
#include "win32_LastError.h"

std::string Win32_LastError() {
  LPVOID lpMsgBuf;
  std::string ret;
  if (!FormatMessage( 
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM     | 
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) &lpMsgBuf,
      0,
      0 )) { return "error with Win32_LastError"; }
  
  ret = (LPCTSTR) lpMsgBuf;
  ::LocalFree(lpMsgBuf);
  return ret;
}
