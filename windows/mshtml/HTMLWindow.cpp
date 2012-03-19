/* HTMLWindow.cpp

   Copyright (C) René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/

#include "HTMLWindow.h"
#include <ExDispId.h>
#include <stdio.h>

#include "OleClientSite.h"
#include "Storage.h"
#include "OleInPlaceSite.h"
#include "OleInPlaceFrame.h"
#include "DocHostUiHandler.h"
#include "Tracer.h"
#include <string>
#include <map>
#include "VariantHelper.h"
#include "win32_Unicode.h"

#include "UrlHelper.h"

bool TODO_bool=false;

bool HTMLWindow::ole_is_initialized_ = false;

const IID IID_IDocHostUIHandler ={0xbd3f23c0,0xd43e,0x11CF,{0x89, 0x3b, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x1a}};


HTMLWindow::HTMLWindow(std::string const& title, HINSTANCE instance) : 
  instance_(instance), browserObject_(0)
{
  TraceFunc("HTMLWindow::HTMLWindow");

  Create(title);
}

HTMLWindow::HTMLWindow(
    std::string const& html_or_url,
    std::string const& title, 
    HINSTANCE   instance,
    bool        is_url) : 

  instance_      (instance),
  browserObject_ (0)
{

  Create(title);

  if (is_url) URL (html_or_url);
  else        HTML(html_or_url);
}

void HTMLWindow::Create(std::string const& title) {
  TraceFunc("HTMLWindow::Create");

  if (!ole_is_initialized_) {
    /* An application, when initializing the WebBrowser Control, should use
       OleInitialize rather than CoInitialize to start COM. OleInitialize
       enables support for the clipboard, drag-and-drop, OLE, and in-place
       activation. Use OleUninitialize to close the COM library when your
       application shuts down.  */

    if (::OleInitialize(0) != S_OK) {
      return;
    }
    ole_is_initialized_ = true;
  }

  WNDCLASSEX    wc;

  ::ZeroMemory (&wc, sizeof(WNDCLASSEX));
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.hInstance     = instance_;
  wc.lpfnWndProc   = this->WindowProc;
  wc.lpszClassName = "subkdls490";

  RegisterClassEx(&wc);

  hwnd_ = ::CreateWindowEx(0, "subkdls490", title.c_str(), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0, 
            CW_USEDEFAULT, 0,
            HWND_DESKTOP , 0, 
            instance_    , 0);

  if (hwnd_) { 
    SetWindowLong(hwnd_, GWL_USERDATA, (LONG)this);
    if (CreateBrowserObject()) {
      ::MessageBox(0, "Could not create browser object", 0, 0);
    }

    AddSink();

    ShowWindow(hwnd_, SW_SHOWNORMAL);
    UpdateWindow(hwnd_);
  }
}

HTMLWindow::~HTMLWindow () {
  if (ole_is_initialized_) {
    ::OleUninitialize();
    ole_is_initialized_ = false;
  }
}

HRESULT HTMLWindow::QueryInterface(REFIID riid, void ** ppvObject) {
  TraceFunc("HTMLWindow::QueryInterface");
  if (!memcmp((const void*) &riid, (const void*)&IID_IUnknown,          sizeof(GUID)) || 
      !memcmp((const void*) &riid, (const void*)&IID_IDispatch,         sizeof(GUID)) ||
      !memcmp((const void*) &riid, (const void*)&IID_IDocHostUIHandler, sizeof(GUID))) {
      TraceFunc("HTMLWindow::QueryInterface");
      *ppvObject = doc_host_ui_handler_;
      return S_OK;
    }

  ppvObject = 0;
  return E_NOINTERFACE;
}

/*
  This method displays the HTML that is passed as a string.
*/
long HTMLWindow::HTML(std::string const& html_txt) {
  IWebBrowser2    *webBrowser2;
  LPDISPATCH       lpDispatch;
  IHTMLDocument2  *htmlDoc2;
  SAFEARRAY       *sfArray;
  VARIANT         *pVar;

  BSTR             bstr_html_txt;

  // bstr_html_txt <> 0 indicates no error.
  //   Here, an error is assumed; but it is also hoped that 
  //   it is actually none
  bstr_html_txt = 0;

  TraceFunc("HTMLWindow::HTML");

  static bool TODO_about_blank_written_once = false;
  if (!TODO_about_blank_written_once) {
    Trace("going to DisplayHTMLPage with about:blank (calling URL)");
    URL("about:blank");
    TODO_about_blank_written_once = true;
  }

  if (!browserObject_->QueryInterface(IID_IWebBrowser2, (void**)&webBrowser2)) {
    if (!webBrowser2->get_Document(&lpDispatch)) {
      if (!lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&htmlDoc2)) {
        
        // A SAFEARRAY is a multi dimensional multi type array. 
        // TODO raus mit dem
        SAFEARRAYBOUND ArrayBound = {1, 0};

        /* The HTML passed to IHTMLDocument2::write must be a 
        BSTR within an array of VARIANTs....  */
        if ((sfArray = SafeArrayCreate(VT_VARIANT, 1, &ArrayBound))) {
          if (!SafeArrayAccessData(sfArray, (void**)&pVar)) {
            pVar->vt = VT_BSTR;
#ifndef UNICODE
            std::wstring ws_html_txt = s2ws(html_txt);
            bstr_html_txt = ::SysAllocString(ws_html_txt.c_str());
#else
            bstr_html_txt = ::SysAllocString(html_txt);
#endif
            if ((pVar->bstrVal = bstr_html_txt)) {
              Trace("Going to actually write sfArray into html document");
              if (htmlDoc2->write(sfArray) != S_OK) {
                throw ("Could not write sfArray");
              }

              /* 
                 If the document were not closed, subsequent calls to 
                 DisplayHTMLStr would append to the contents of the page.  */
              htmlDoc2->close();
              Trace("Closing document");
            }
          }

          /*
            Freeing the array along with the VARIANT that SafeArrayAccessData 
            created and the BSTR that was allocated with SysAllocString */
          SafeArrayDestroy(sfArray);
        }

        htmlDoc2->Release();
      }

      lpDispatch->Release();
    }

    webBrowser2->Release();
  }

  // bstr_html_txt <> 0 indicates no error
  if (bstr_html_txt) return 0;

  return(-1);
}

long HTMLWindow::CreateBrowserObject() {
  TraceFunc("HTMLWindow::CreateBrowserObject");
  RECT             rect;

  // RENE 
#define OLERENDER_DRAW 1

  storage_            = new Storage;

  ole_in_place_frame_ = new OleInPlaceFrame(hwnd_);
  ole_in_place_site_  = new OleInPlaceSite(ole_in_place_frame_, hwnd_);;
  doc_host_ui_handler_= new DocHostUiHandler(this);

  ole_client_site_ = new OleClientSite(
      ole_in_place_site_, 
      doc_host_ui_handler_,
      static_cast<DWebBrowserEvents2*>(this));

  doc_host_ui_handler_->ClientSite(ole_client_site_);
  ole_in_place_site_  ->ClientSite(ole_client_site_);

  // OleCreate creates an embedded object. In this case here, the object is identified
  // by CLSID_WebBrowser
  //
  // IID_IOleObject identifies the interface that is used to communicate
  // with the the new object
  //
  // OLERENDER_DRAW: indicates which cached render capabilites there are
  if (! ::OleCreate(
         CLSID_WebBrowser,
         IID_IOleObject,
         OLERENDER_DRAW,
         0,
         ole_client_site_,
         storage_,
         (void**)&browserObject_)) {

    ole_in_place_site_->BrowserObject(browserObject_);

    browserObject_ -> SetHostNames(L"Some_host_name", 0);

    ::GetClientRect(hwnd_, &rect);

    IWebBrowser2    *webBrowser2;
    // Notify browserObject_ that it is now contained in an OLE container
    // OleSetContainedObject ensures correct reference counting
    Trace("Calling browserObject_->DoVerb (OLEIVERB_SHOW)");
    if (! ::OleSetContainedObject(static_cast<IUnknown*>(browserObject_), TRUE) &&
      // Setting the display area of the browser control
      !browserObject_->DoVerb(OLEIVERB_SHOW, NULL, 
       ole_client_site_,
        -1, hwnd_, &rect) &&

      !browserObject_->QueryInterface(IID_IWebBrowser2, reinterpret_cast<void**> (&webBrowser2) )  
    )
    { 
      webBrowser2->put_Left  (0);
      webBrowser2->put_Top   (0);
      webBrowser2->put_Width (rect.right);
      webBrowser2->put_Height(rect.bottom);

      webBrowser2->Release();
      return 0;
    }

    ::MessageBox(0, "Something went wrong -3", 0, 0);
    /* Something went wrong!
     TODO  UnEmbedBrowserObject(hwnd_); */
    return(-3);
  }

  ::MessageBox(0, "Something went wrong -2", 0, 0);

  return -2 ;
}

void HTMLWindow::Resize(DWORD width, DWORD height) {
  IWebBrowser2  *webBrowser2;

  if (!browserObject_->QueryInterface(IID_IWebBrowser2, (void**)&webBrowser2)) {

    webBrowser2->put_Width(width);
    webBrowser2->put_Height(height);

    webBrowser2->Release();
  }
  else {
    ::MessageBox(0, "Couldn't query interface for IID_IWebBrowser2", 0, 0);
  }
}

// See also:
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/automat/htm/chap6_7zdz.asp
HRESULT HTMLWindow::Invoke( 
    DISPID             dispIdMember,      
    REFIID             /*riid*/,              
    LCID               /*lcid        */ ,               
    WORD               /*wFlags      */ ,             
    DISPPARAMS FAR*    pDispParams      , 
    VARIANT FAR*       /*pVarResult  */ , 
    EXCEPINFO FAR*     /*pExcepInfo  */ , 
    unsigned int FAR*  /*puArgErr    */
    ) {
      /* 
         _______________
         From ExDispid.h
      ---===============---

      
     The constants passed through dispIdMember seem to be defined in ExDispId.h.
     However, in the MinGw distribution, only a few are defined, much less than
     in Microsofts Platform SDK.
     So, I am defininig those that I need here....
  */
#define DISPID_BEFORENAVIGATE     100   // this is sent before navigation to give a chance to abort
#define DISPID_COMMANDSTATECHANGE 105
#define DISPID_NAVIGATECOMPLETE2    252   // UIActivate new document
#define DISPID_NAVIGATEERROR        271   // Fired to indicate the a binding error has occured
#define DISPID_DOWNLOADCOMPLETE   104
#define DISPID_DOWNLOADBEGIN      106
#define DISPID_PROPERTYCHANGE     112   // sent when the PutProperty method is called
#define DISPID_SETSECURELOCKICON    269   // sent to suggest the appropriate security icon to show
//#define DISPID_PROGRESSCHANGE     108   // sent when download progress is updated
  switch (dispIdMember) {
  case DISPID_BEFORENAVIGATE     :   // this is sent before navigation to give a chance to abort
    ::MessageBox(0, "Before Navigate", 0, 0);
    return S_OK;
    break;
//  case DISPID_NAVIGATECOMPLETE   :   // in async, this is sent when we have enough to show
//
//    ::MessageBox(0, "Download complete", 0, 0);
//  break;
  case DISPID_STATUSTEXTCHANGE   :
  //case DISPID_QUIT               :
  case DISPID_DOWNLOADCOMPLETE: 
    return S_OK;
  case DISPID_COMMANDSTATECHANGE :
    return S_OK;
    break;
  case DISPID_DOWNLOADBEGIN      :
    return S_OK;
  break;
  //case DISPID_NEWWINDOW          :   // sent when a new window should be created
  case DISPID_PROGRESSCHANGE     :   // sent when download progress is updated
  //case DISPID_WINDOWMOVE         :   // sent when main window has been moved
  //case DISPID_WINDOWRESIZE       :   // sent when main window has been sized
  //case DISPID_WINDOWACTIVATE     :   // sent when main window has been activated
  case DISPID_PROPERTYCHANGE: {   // sent when the PutProperty method is called
    VARIANT a = pDispParams->rgvarg[0];
    
    return S_OK;
  }
  case DISPID_TITLECHANGE        :   // sent when the document title changes
  //case DISPID_TITLEICONCHANGE    :   // sent when the top level window icon may have changed.
  //case DISPID_FRAMEBEFORENAVIGATE    :
  //case DISPID_FRAMENAVIGATECOMPLETE  :
  //case DISPID_FRAMENEWWINDOW         :
  return S_OK;
  break;

  // DISPID_BEFORENAVIGATE2 replaces BeforeNavigate and FrameBeforeNavigate. These should not be
  // used anymore.
  case DISPID_BEFORENAVIGATE2: {   // hyperlink clicked on
    TraceFunc("DWebBrowserEvents2::BeforeNavigate2 ");

    VARIANT vURL_p = pDispParams->rgvarg[5];
    VARIANT vURL = *(vURL_p.pvarVal);

    VARIANT  vCANCEL = pDispParams->rgvarg[0];
    std::string type = VariantTypeAsString(vCANCEL);

    std::wstring ws_url = vURL.bstrVal;

    std::string url = ws2s(ws_url);

    Trace2("url=", url);

    if (BeforeNavigate(url)) {
      *(vCANCEL.pbool) = VARIANT_FALSE;
    }
    else {
      *(vCANCEL.pbool) = VARIANT_TRUE;

      VARIANT vDisp = pDispParams->rgvarg[6];
      IDispatch* disp=vDisp.pdispVal;
      
      IWebBrowser2* webBrowser;
      disp->QueryInterface(IID_IWebBrowser2, reinterpret_cast<void**>(&webBrowser));
      webBrowser->Stop();
    }
    
    return S_OK;
  }
  break;
  case DISPID_NEWWINDOW2:          
    return S_OK;
  case DISPID_NAVIGATECOMPLETE2:       // UIActivate new document
    return S_OK;
    break;
  //case DISPID_ONQUIT               :
  //case DISPID_ONVISIBLE            :   // sent when the window goes visible/hidden
  //case DISPID_ONTOOLBAR            :   // sent when the toolbar should be shown/hidden
  //case DISPID_ONMENUBAR            :   // sent when the menubar should be shown/hidden
  //case DISPID_ONSTATUSBAR          :   // sent when the statusbar should be shown/hidden
  //case DISPID_ONFULLSCREEN         :   // sent when kiosk mode should be on/off
  case DISPID_DOCUMENTCOMPLETE     :   // new document goes ReadyState_Complete
    //AddSink();
    return S_OK;
  //case DISPID_ONTHEATERMODE        :   // sent when theater mode should be on/off
  //case DISPID_ONADDRESSBAR         :   // sent when the address bar should be shown/hidden
  //case DISPID_WINDOWSETRESIZABLE   :   // sent to set the style of the host window frame
  //case DISPID_WINDOWCLOSING        :   // sent before script window.close closes the window 
  //case DISPID_WINDOWSETLEFT        :   // sent when the put_left method is called on the WebOC
  //case DISPID_WINDOWSETTOP         :   // sent when the put_top method is called on the WebOC
  //case DISPID_WINDOWSETWIDTH       :   // sent when the put_width method is called on the WebOC
  //case DISPID_WINDOWSETHEIGHT      :   // sent when the put_height method is called on the WebOC 
  //case DISPID_CLIENTTOHOSTWINDOW   :   // sent during window.open to request conversion of dimensions
  //case DISPID_SETSECURELOCKICON    :   // sent to suggest the appropriate security icon to show
  //case DISPID_FILEDOWNLOAD         :   // Fired to indicate the File Download dialog is opening
  case DISPID_NAVIGATEERROR: {   // Fired to indicate the a binding error has occured
    char buf[200];
    VARIANT StatusCode=*((pDispParams->rgvarg[1]).pvarVal);
    sprintf(buf, "Navigate Error, code is: %d", static_cast<int>(StatusCode.lVal));
    MessageBox(0, buf, 0, 0);
  //case DISPID_PRIVACYIMPACTEDSTATECHANGE   :  // Fired when the user's browsing experience is impacted
   return S_OK;
  }
  default:
    char buf[50];
    sprintf(buf, "invoke, dispid: %d", static_cast<int>(dispIdMember));
    if (TODO_bool) ::MessageBox(0, buf, 0, 0);
    return DISP_E_MEMBERNOTFOUND;
  }
}

void HTMLWindow::AddSink() {
  TraceFunc("HTMLWindow::AddSink");
  IConnectionPointContainer* cpc;
  IConnectionPoint*          cp;

  if (!browserObject_) {
    ::MessageBox(0, "browserObject_ is null in AddSink", 0, 0);
    return;
  }
  if (browserObject_->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<void**>(&cpc)) == S_OK) {
    if (cpc->FindConnectionPoint(DIID_DWebBrowserEvents2, &cp) == S_OK) {

      // TODO: Member Var
      unsigned long cookie = 1;
      if (! (SUCCEEDED(cp->Advise(static_cast<IDispatch*>(this), &cookie)) ) ) {
        ::MessageBox(0, "Advise failed", 0, 0);
      }
    }
    else {
      ::MessageBox(0, "FindConnectionPoint", 0, 0);
    }
  }
  else {
    ::MessageBox(0, "QueryInterface for IID_IConnectionPointContainer", 0, 0);
  }
}

void HTMLWindow::Size(int width, int height) {
  RECT r;
  ::GetWindowRect(hwnd_, &r);

  ::MoveWindow(hwnd_, r.left, r.top, width, height, true);
}

LRESULT CALLBACK HTMLWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_SIZE: {
      HTMLWindow* win = reinterpret_cast<HTMLWindow*> (::GetWindowLong(hwnd, GWL_USERDATA));
      if (win) {
        win->Resize(LOWORD(lParam), HIWORD(lParam));
      }
      return 0;
    }

    case WM_CREATE: {
      return 0;
    }

    case WM_DESTROY: {
      PostQuitMessage(0);
      return TRUE;
    }

    case WM_KEYDOWN: {
      TraceFunc("WM_KEYDOWN in HTMLWindow");
      Trace2("wParam: ", wParam);
      if (wParam == VK_TAB) {
        /*
           The following code is necessary to enable 'tabulator navigating' in forms.
           See also http://www.microsoft.com/0499/faq/faq0499.asp
           and the SendMessage part in the MessageLoop
        */
        IOleInPlaceActiveObject* ipao;
        IWebBrowser2  *webBrowser2;
        HTMLWindow* win = reinterpret_cast<HTMLWindow*> (::GetWindowLong(hwnd, GWL_USERDATA));
        if (win) {
          if (!win->browserObject_->QueryInterface(IID_IWebBrowser2, (void**)&webBrowser2)) {
            webBrowser2->QueryInterface(IID_IOleInPlaceActiveObject, reinterpret_cast<void**>(&ipao));
            if (ipao) {
              MSG m;
              m.message=WM_KEYDOWN;
              m.wParam = wParam;
              m.lParam = lParam;
              m.hwnd   = hwnd;

              ipao->TranslateAccelerator(&m);
            }
            else {
              ::MessageBox(0, "Failed to retrieve IOleInPlaceActiveObject in WM_KEYDOWN", 0, 0);
            }
          }
          return 0;
        }
        else {
          ::MessageBox(0, "Failed to retrieve webBrowser2 in WM_KEYDOWN", 0, 0);
        }
        return -1;
      }
      break;
    }
    
    case WM_APP: {
     
      TraceFunc("WM_APP called"); 
      HTMLWindow*  win               = reinterpret_cast<HTMLWindow* >(::GetWindowLong(hwnd, GWL_USERDATA));
      std::string* path_with_params  = reinterpret_cast<std::string*>(wParam);
      std::string path;
      std::map<std::string,std::string> params;

      Trace(std::string("path_with_params: ") + *path_with_params);

      SplitGetReq(*path_with_params, path, params);

      Trace(std::string("path: ") + path);

      std::string out_html;

      win->AppLink(path, out_html, params);

      win->HTML(out_html);

      // url is allocated in DOCHostHandler.cpp
      Trace("going to delete url");
      //delete url;
      delete path_with_params;
      // param_map is allocated in DOCHostHandler.cpp
      Trace("going to delete param_map");

      //delete param_map;
      Trace("param_map deleted");
      return 0;
    }
  }

  return(DefWindowProc(hwnd, uMsg, wParam, lParam));
}

/* This method shows an URL */
long HTMLWindow::URL(std::string const& url) {
  IWebBrowser2  *webBrowser2;
  VARIANT         vURL;
  ::VariantInit(&vURL);
  vURL.vt = VT_BSTR;

  TraceFunc("HTMLWindow::URL");
  Trace( (std::string("url is: ") + url).c_str());

  if (!browserObject_->QueryInterface(IID_IWebBrowser2, (void**)&webBrowser2)) {

#ifndef UNICODE
    std::wstring ws_url = s2ws(url);
    vURL.bstrVal = ::SysAllocString(ws_url.c_str());
#else
    vURL.bstrVal = ::SysAllocString(url);
#endif
    if (!vURL.bstrVal) {
      webBrowser2->Release();
      return(-6);
    }

    // Navigate2 navigates to the passed url.
    // Navigating to about:blank ensures that MSHTML is loaded.
    webBrowser2->Navigate2(&vURL, 0, 0, 0, 0);

    VariantClear(&vURL);

    webBrowser2->Release();

    return 0 ;
  }

  Trace("Something went wrong, returning -5");
  return(-5);
}
