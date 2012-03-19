#include "DocHostUiHandler.h"
#include "HTMLWindow.h"
#include <string>
#include <map>

#include "Tracer.h"
#include "UrlHelper.h"

DocHostUiHandler::DocHostUiHandler(HTMLWindow* w) :
  ole_client_site_(0),
  html_window_    (w)
{
}

void DocHostUiHandler::ClientSite(IOleClientSite* o) {
  ole_client_site_ = o;
}

/* TranslateUrl is called by MSHTML to give the host an opportunity to modify the URL
   to be loaded.  */
HRESULT STDMETHODCALLTYPE DocHostUiHandler::TranslateUrl (
     DWORD                         /*dwTranslate*/, 
     OLECHAR __RPC_FAR*            pchURLIn, 
     OLECHAR __RPC_FAR* __RPC_FAR* ppchURLOut) {

  TraceFunc("DocHostUiHandler::TranslateUrl");

  DWORD size = ::WideCharToMultiByte(
       CP_ACP, 
       0, 
       pchURLIn, 
       -1,  // number of chars in string. If -1, string is assumed to be 0 terminated
       0, 0, 0, 0);
  char* buf = new char[size];

  ::WideCharToMultiByte(
      CP_ACP,
      0,
      pchURLIn,
      -1,
      buf, size, 0, 0);

  std::string url = buf;
  delete [] buf;

  Trace(std::string("called with '") + url.c_str() + "'");

  std::string protocol;
  std::string rest;
  if (RemoveProtocolFromUrl(url, protocol, rest)) {
    Trace(std::string("protocol is: '") + protocol + "'");
    Trace(std::string("rest is: '") + rest + "'");
    if (protocol == "link") {

      Trace("going to PostMessage WM_APP");
      /*
        The message that is posted here is going to be catched in
        the WindowProc in HTMLWindow.cpp
      */
      PostMessage(html_window_->hwnd_, WM_APP, reinterpret_cast<WPARAM>(new std::string(rest)), 0);
      Trace("posted WM_APP");
  
      *ppchURLOut = L"about:blank";
      
      Trace("Returning S_OK");
      return S_OK;
    }
  }
  *ppchURLOut = pchURLIn;
  return S_OK;
}

HRESULT DocHostUiHandler::ShowContextMenu (
      DWORD                /*dwID*/, 
      POINT     __RPC_FAR* /*ppt*/, 
      IUnknown  __RPC_FAR* /*pcmdtReserved*/, 
      IDispatch __RPC_FAR* /*pdispReserved*/)  {

  TraceFunc("DocHostUiHandler::ShowContextMenu");

  return S_OK;
}


/* Be sure to use CoTaskMemAlloc to allocate strings for pchHostCss or pchHostNS.  */
HRESULT DocHostUiHandler::GetHostInfo(DOCHOSTUIINFO __RPC_FAR *pInfo) {
  pInfo->cbSize = sizeof(DOCHOSTUIINFO);

  pInfo->dwFlags = 
   // DOCHOSTUIFLAG_DIALOG                     |
   // DOCHOSTUIFLAG_DISABLE_HELP_MENU          |
      DOCHOSTUIFLAG_NO3DBORDER                 |  /* No 3D Border   */
   // DOCHOSTUIFLAG_SCROLL_NO                  |  /* Hide Scrollbar */
   // DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE    |
   // DOCHOSTUIFLAG_OPENNEWWIN                 |
   // DOCHOSTUIFLAG_DISABLE_OFFSCREEN          |
   // DOCHOSTUIFLAG_FLAT_SCROLLBAR             |
   // DOCHOSTUIFLAG_DIV_BLOCKDEFAULT           |
   // DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY    |
   // DOCHOSTUIFLAG_OVERRIDEBEHAVIORFACTORY    |
   // DOCHOSTUIFLAG_CODEPAGELINKEDFONTS        |
   // DOCHOSTUIFLAG_URL_ENCODING_DISABLE_UTF8  |
   // DOCHOSTUIFLAG_URL_ENCODING_ENABLE_UTF8   |
   // DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE  |
   // DOCHOSTUIFLAG_ENABLE_INPLACE_NAVIGATION  | 
   // DOCHOSTUIFLAG_IME_ENABLE_RECONVERSION    |
   // DOCHOSTUIFLAG_THEME                      |
   // DOCHOSTUIFLAG_NOTHEME                    |
   // DOCHOSTUIFLAG_NOPICS                     |
      DOCHOSTUIFLAG_NO3DOUTERBORDER            |
      0                                        ;

  // What happens if user double clicks?
  pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

  return S_OK ;
}

HRESULT DocHostUiHandler::GetExternal(IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) {
  *ppDispatch = 0;
  return S_FALSE;
}

HRESULT DocHostUiHandler::GetOptionKeyPath(LPOLESTR __RPC_FAR* /*pchKey*/, DWORD /*dw*/) {
  return S_FALSE;
}

HRESULT DocHostUiHandler::TranslateAccelerator(
    LPMSG /*lpMsg*/, 
    const GUID __RPC_FAR* /*pguidCmdGroup*/, 
    DWORD /*nCmdID*/) {
  TraceFunc("DocHostUiHandler::TranslateAccelerator");

  return S_FALSE;
}

