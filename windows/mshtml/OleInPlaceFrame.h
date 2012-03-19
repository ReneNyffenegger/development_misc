/* 
   OleInPlaceFrame.h

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

#ifndef OLE_IN_PLACE_FRAME_H__
#define OLE_IN_PLACE_FRAME_H__ 

#include <windows.h>

#include "Tracer.h"

class OleInPlaceFrame : public IOleInPlaceFrame {
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID /*riid*/, LPVOID FAR* /*ppvObj*/) {
  	MUST_BE_IMPLEMENTED("QueryInterface")
  }
  
  ULONG STDMETHODCALLTYPE AddRef() {return 1;}
  
  ULONG STDMETHODCALLTYPE Release() {return 1;}
  
  HRESULT STDMETHODCALLTYPE GetWindow(HWND FAR* lphwnd) {
  	//*lphwnd = TODO_hwnd;
  	*lphwnd = hwnd_;
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL /*fEnterMode*/) { MUST_BE_IMPLEMENTED("ContextSensitiveHelp") }
  
  HRESULT STDMETHODCALLTYPE GetBorder(LPRECT /*lprectBorder*/) { MUST_BE_IMPLEMENTED("GetBorder") }
  
  HRESULT STDMETHODCALLTYPE RequestBorderSpace(LPCBORDERWIDTHS /*pborderwidths*/) { MUST_BE_IMPLEMENTED("RequestBorderSpace") }
  
  HRESULT STDMETHODCALLTYPE SetBorderSpace(LPCBORDERWIDTHS /*pborderwidths*/) { MUST_BE_IMPLEMENTED("SetBorderSpace") }
  
  HRESULT STDMETHODCALLTYPE SetActiveObject(IOleInPlaceActiveObject* /*pActiveObject*/, LPCOLESTR /*pszObjName*/) { return S_OK; }
  
  HRESULT STDMETHODCALLTYPE InsertMenus(HMENU /*hmenuShared*/, LPOLEMENUGROUPWIDTHS /*lpMenuWidths*/) {MUST_BE_IMPLEMENTED("InsertMenus") }
  
  HRESULT STDMETHODCALLTYPE SetMenu(HMENU /*hmenuShared*/, HOLEMENU /*holemenu*/, HWND /*hwndActiveObject*/) { return(S_OK); }
  
  HRESULT STDMETHODCALLTYPE RemoveMenus(HMENU /*hmenuShared*/) {MUST_BE_IMPLEMENTED("RemoveMenus") }
  
  HRESULT STDMETHODCALLTYPE SetStatusText(LPCOLESTR /*pszStatusText*/) {return S_OK;}
  
  HRESULT STDMETHODCALLTYPE EnableModeless(BOOL /*fEnable*/) { return S_OK; }
  
  HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG /*lpmsg*/, WORD /*wID*/) {
    TraceFunc("OleInPlaceFrame::TranslateAccelerator");
  	MUST_BE_IMPLEMENTED("TranslateAccelerator")
  }

  public:
  OleInPlaceFrame(HWND h) {hwnd_=h;}

  private:
    HWND hwnd_;
};

#endif

