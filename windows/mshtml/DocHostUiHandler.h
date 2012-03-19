/* 
   DocHostUiHandler.h

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

#include <windows.h>
#include <ExDisp.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <oaidl.h>

#ifndef DOC_HOST_UI_HANDLER_H__
#define DOC_HOST_UI_HANDLER_H__

/*
   IDocHostUIHandler, along with IDocHostShowUI, is used to obtain extra control.

   This interface is obtained by calling QueryInterface on IOleClientSite

*/
class DocHostUiHandler : public IDocHostUIHandler {

  IOleClientSite*   ole_client_site_;
  class HTMLWindow* html_window_;

  public:

  void ClientSite(IOleClientSite*);

  DocHostUiHandler(class HTMLWindow*);

  virtual 
 ~DocHostUiHandler() {} 

  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID FAR* ppvObj) {
    if (ole_client_site_) {
      return ole_client_site_->QueryInterface(riid, ppvObj);
    }
  
    ::MessageBox(0, "ClientSite is null", 0, 0);
  
    return E_NOINTERFACE;
  }
  
  ULONG STDMETHODCALLTYPE AddRef() {
  	return 1;
  }
  
  ULONG STDMETHODCALLTYPE Release() {
  	return 1;
  }

  /*
      This method is for example called when the right mouse button is pressed.

      Returning S_OK does not display a menu at all
      Returning S_NOTIMPL or S_FALSE lets the web browser control display its own menus.
  */
  HRESULT STDMETHODCALLTYPE ShowContextMenu(
      DWORD                dwID, 
      POINT     __RPC_FAR *ppt, 
      IUnknown  __RPC_FAR *pcmdtReserved, 
      IDispatch __RPC_FAR *pdispReserved);
  
  HRESULT STDMETHODCALLTYPE ShowUI(
      DWORD                              /*dwID*/, 
      IOleInPlaceActiveObject __RPC_FAR* /*pActiveObject*/, 
      IOleCommandTarget       __RPC_FAR* /*pCommandTarget*/, 
      IOleInPlaceFrame        __RPC_FAR* /*pFrame*/, 
      IOleInPlaceUIWindow     __RPC_FAR* /*pDoc*/) 
  {
  	return S_OK ;
  }

  HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO __RPC_FAR* /*pInfo*/);
  
  HRESULT STDMETHODCALLTYPE HideUI() {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE UpdateUI() {
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE EnableModeless(BOOL /*fEnable*/) {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL /*fActivate*/) {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL /*fActivate*/) {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT /*prcBorder*/, IOleInPlaceUIWindow __RPC_FAR* /*pUIWindow*/, BOOL /*fRameWindow*/) {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg, const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID);

  HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR __RPC_FAR* /*pchKey*/, DWORD /*dw*/);
  
  HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget __RPC_FAR* /*pDropTarget*/, IDropTarget __RPC_FAR* __RPC_FAR* /*ppDropTarget*/) {
    /*
  	 Return our IDropTarget object associated with this IDocHostUIHandler object. I don't
  	 know why we don't do this via QueryInterface(), but we don't.
  
  	 NOTE: If we want/need an IDropTarget interface, then we would have had to setup our own
  	 IDropTarget functions, IDropTarget VTable, and create an IDropTarget object. We'd want to put
  	 a pointer to the IDropTarget object in our own custom IDocHostUIHandlerEx object (like how
  	 we may add an HWND field for the use of ShowContextMenu). So when we created our
  	 IDocHostUIHandlerEx object, maybe we'd add a 'idrop' field to the end of it, and
  	 store a pointer to our IDropTarget object there. Then we could return this pointer as so:
  	
  	 *pDropTarget = ((IDocHostUIHandlerEx FAR *)This)->idrop;
      return S_OK;
  
  	 But for our purposes, we don't need an IDropTarget object, so we'll tell whomever is calling
  	 us that we don't have one. */
     return S_FALSE;
  }
  
  HRESULT STDMETHODCALLTYPE GetExternal(IDispatch __RPC_FAR* __RPC_FAR* /*ppDispatch*/);
  
  HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate, OLECHAR __RPC_FAR* /*pchURLIn*/, OLECHAR __RPC_FAR* __RPC_FAR* /*ppchURLOut*/); 
  
  HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject __RPC_FAR* /*pDO*/, IDataObject __RPC_FAR* __RPC_FAR* ppDORet) {
    /*
  	 Return our IDataObject object associated with this IDocHostUIHandler object. I don't
  	 know why we don't do this via QueryInterface(), but we don't.
  
  	 NOTE: If we want/need an IDataObject interface, then we would have had to setup our own
  	 IDataObject functions, IDataObject VTable, and create an IDataObject object. We'd want to put
  	 a pointer to the IDataObject object in our custom _IDocHostUIHandlerEx object (like how
  	 we may add an HWND field for the use of ShowContextMenu). So when we defined our
  	 _IDocHostUIHandlerEx object, maybe we'd add a 'idata' field to the end of it, and
  	 store a pointer to our IDataObject object there. Then we could return this pointer as so:
  	
  	 *ppDORet = ((_IDocHostUIHandlerEx FAR *)This)->idata;
      return S_OK;
  
  	 But for our purposes, we don't need an IDataObject object, so we'll tell whomever is calling
  	 us that we don't have one. Note: We must set ppDORet to 0 if we don't return our own
  	 IDataObject object. */
  	*ppDORet = 0;
  	return S_FALSE;
  }
};

#endif
