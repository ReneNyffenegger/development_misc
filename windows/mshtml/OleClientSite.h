/* 
   OleClientSite.h

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

#ifndef OLE_CLIENT_SITE_H__
#define OLE_CLIENT_SITE_H__

#include <windows.h>
#include <ExDisp.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <oaidl.h>

#include "Tracer.h"

/*
   An embedded object (such as the web browser) used an IOleClientSite interface
   to obtain some information about the location and extent of the embedded object's 
   display site.
*/
class OleClientSite : public IOleClientSite {

  IOleInPlaceSite   * in_place_;
  IDocHostUIHandler * doc_host_ui_handler_;
  DWebBrowserEvents2* web_browser_events_;

  public:

    OleClientSite (
        IOleInPlaceSite*    in_place,
        IDocHostUIHandler*  doc_host_ui_handler,
        DWebBrowserEvents2* web_browser_events);

  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject);
  
  ULONG STDMETHODCALLTYPE AddRef() {return 1;}
  
  ULONG STDMETHODCALLTYPE Release() {return 1;}
  
  HRESULT STDMETHODCALLTYPE SaveObject() {MUST_BE_IMPLEMENTED("SaveObject") }
  
  HRESULT STDMETHODCALLTYPE GetMoniker(DWORD /*dwAssign*/, DWORD /*dwWhichMoniker*/, IMoniker** /*ppmk*/) { MUST_BE_IMPLEMENTED("GetMoniker") }
  
  HRESULT STDMETHODCALLTYPE GetContainer(LPOLECONTAINER FAR* ppContainer) {
    TraceFunc("OleClientSite::GetContainer");
  	// No container in sight....
  	*ppContainer = 0;
  
  	return E_NOINTERFACE;
  }
  
  HRESULT STDMETHODCALLTYPE ShowObject() {
    TraceFunc("OleClientSite::ShowObject");
    return NOERROR;}
  
  HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL /*fShow*/) {MUST_BE_IMPLEMENTED("OnShowWindow") }
  
  HRESULT STDMETHODCALLTYPE RequestNewObjectLayout() {MUST_BE_IMPLEMENTED("RequestNewObjectLayout") }
};

#endif
