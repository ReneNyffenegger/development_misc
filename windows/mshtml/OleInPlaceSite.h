/* 
   OleInPlaceSite.h

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

#ifndef OLE_IN_PLACA_SITE_H__
#define OLE_IN_PLACA_SITE_H__

#include <windows.h>

class OleInPlaceSite : public IOleInPlaceSite {
  private:
     class IOleClientSite*   ole_client_site_;
     class IOleInPlaceFrame* ole_in_place_frame_;
	   class IOleObject			 * browser_object_;
     HWND                    hwnd_;

  public:
     OleInPlaceSite(class IOleInPlaceFrame* ole_in_place_frame_, HWND h);

  HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, LPVOID FAR* ppvObj); 

  ULONG STDMETHODCALLTYPE AddRef() { return(1); }
  
  ULONG STDMETHODCALLTYPE Release() { return(1); }
  
  HRESULT STDMETHODCALLTYPE GetWindow( HWND FAR* lphwnd) {
    *lphwnd = hwnd_;
  	return(S_OK);
  }
  
  HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL /* fEnterMode*/) {
  	MUST_BE_IMPLEMENTED("ContextSensitiveHelp")
  }
  
  HRESULT STDMETHODCALLTYPE CanInPlaceActivate() {
  	// In place activate is OK
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE OnInPlaceActivate() {
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE OnUIActivate() { return(S_OK); }
  
  HRESULT STDMETHODCALLTYPE GetWindowContext(
      LPOLEINPLACEFRAME    FAR* lplpFrame, 
      LPOLEINPLACEUIWINDOW FAR* lplpDoc, 
      LPRECT                    /*lprcPosRect*/, 
      LPRECT                    /*lprcClipRect*/, 
      LPOLEINPLACEFRAMEINFO     lpFrameInfo) {

    *lplpFrame = ole_in_place_frame_;
  
  	// There is no OLEINPLACEUIWINDOW
  	*lplpDoc = 0;
  
  	// Fill in some other info for the browser
  	lpFrameInfo->fMDIApp       = FALSE;
  	lpFrameInfo->hwndFrame     = hwnd_;
  	lpFrameInfo->haccel        = 0;
  	lpFrameInfo->cAccelEntries = 0;
  
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE Scroll(SIZE /*scrollExtent*/) { MUST_BE_IMPLEMENTED("Scroll") }
  
  HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL /*fUndoable*/) { return(S_OK); }
  
  HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate() { return(S_OK); }
  
  HRESULT STDMETHODCALLTYPE DiscardUndoState() {MUST_BE_IMPLEMENTED("DiscardUndoState") }
  
  HRESULT STDMETHODCALLTYPE DeactivateAndUndo() {MUST_BE_IMPLEMENTED("DeactivateAndUndo") }
  
  // Called when the position of the browser object is changed, such as when we call the IWebBrowser2's put_Width(), // put_Height(), put_Left(), or put_Right().
  HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect) {
  	IOleInPlaceObject	*inplace;
  	if (!browser_object_->QueryInterface(IID_IOleInPlaceObject, (void**)&inplace)) {
  		inplace->SetObjectRects(lprcPosRect, lprcPosRect);
  	}
  
  	return(S_OK);
  }
  
  void BrowserObject(IOleObject* o);

  void ClientSite(IOleClientSite* o) {ole_client_site_=o;}
};

#endif

