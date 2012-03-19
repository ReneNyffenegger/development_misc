/* 
   HTMLWindow.h

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

#ifndef HTMLWINDOW_H__
#define HTMLWINDOW_H__

#include <windows.h>
#include <exdisp.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <oaidl.h>

#include <string>
#include <map>

// TODO
#define MUST_BE_IMPLEMENTED(s) ::MessageBox(0, s, "Not Implemented", 0);  return E_NOTIMPL;

#include "OleClientSite.h"
#include "OleInPlaceSite.h"
#include "OleInPlaceFrame.h"
#include "DocHostUiHandler.h"


/*
  Thanks to http://www.codeproject.com/com/cwebpage.asp for a great example
*/

class HTMLWindow : public virtual DWebBrowserEvents2 {
  public:
  	virtual ~HTMLWindow();

  public:
    class Parameters {
      friend class HTMLWindow;

      // TODO: Parameters should be private
      public:
      Parameters(std::map<std::string,std::string> p) {
        parameters_ = p;
      }
      std::map<std::string, std::string> parameters_;

      public:
        std::string Value(std::string const& name) const {
          if (parameters_.find(name) != parameters_.end()) {
            return parameters_.find(name)->second.c_str();
          }
          else {
            return "";
          }
        }
    };

  protected:
   /*
      The following method is called when a link is clicked whose protocol is link://
      So, in order to make use of this mechanism, one has to inherit from
      HTMLWindow and override AppLink.
   */
    virtual void AppLink(
         std::string const& /* path     */, 
         std::string&       /* out_html */, 
         const Parameters&  /* params   */) {};

  private:
  friend class DocHostUiHandler;

  public:
    typedef std::map<std::string, std::string> param_list;

    HTMLWindow(std::string const& html_or_url,
               std::string const& title, 
               HINSTANCE,
               bool is_url);

    HTMLWindow(
               std::string const& title, 
               HINSTANCE 
//               std::string const& first_link = "start_link", 
//               param_list  const& first_params = param_list()
               );

    long HTML(std::string const&);
    long URL (std::string const& url);
    void AddSink();

    void Size(int width, int height);

    HWND               hwnd_;

  private:
    static bool ole_is_initialized_;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    long CreateBrowserObject();

    void Create(std::string const& title);

    void Resize(DWORD width, DWORD height);

    HINSTANCE          instance_;

    /* An IOleObject is used by an embedded object to provide basic functionality to its
       container */
    IOleObject*        browserObject_;

    OleClientSite*     ole_client_site_;
    IStorage*          storage_;
    OleInPlaceSite*    ole_in_place_site_;
    OleInPlaceFrame*   ole_in_place_frame_;
    DocHostUiHandler*  doc_host_ui_handler_;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject);

    ULONG STDMETHODCALLTYPE AddRef()  {return 1;}

    ULONG STDMETHODCALLTYPE Release() {return 1;}

  void STDMETHODCALLTYPE BeforeNavigate2(          
    IDispatch*    /*pDisp  */,
    VARIANT*      /*url */,
    VARIANT*      /*Flags */,
    VARIANT*      /*TargetFrameName */,
    VARIANT*      /*PostData */,
    VARIANT*      /*Headers */,
    VARIANT_BOOL* Cancel
  ) {
    ::MessageBox(0, "-- BeforeNavigate2", 0, 0);
    *Cancel = 0;
  }

  void ClientToHostWindow(          
    long* /*CX*/,
    long* /*CY*/
  ) {}

  void CommandStateChange(          
      long         /*Command*/,
      VARIANT_BOOL /*Enable */
  ) {}

  void DocumentComplete(          
    IDispatch* /*pDisp*/,
    VARIANT*   /*URL  */
  ) {}

  void DownloadBegin() {}

  void DownloadComplete() {}

  void FileDownload(
      VARIANT_BOOL* /*Cancel*/) 
  {}

  void NavigateComplete(IDispatch* /*pDisp*/, VARIANT* /*URL*/) {}

  void NavigateError(          
    IDispatch*    /*pDisp*/,
    VARIANT*      /*URL*/,
    VARIANT*      /*TargetFrameName*/,
    VARIANT*      /*StatusCode*/,
    VARIANT_BOOL* /*Cancel*/
  ) {
      ::MessageBox(0, "NavigateError", 0, 0);
  }

  void NewWindow2(
    IDispatch**   /*ppDisp*/,
    VARIANT_BOOL* /*Cancel*/
  ) {}

  void OnFullScreen(VARIANT_BOOL /*FullScreen*/) {}

  void OnMenuBar(VARIANT_BOOL /*MenuBar*/) {}

  void OnQuit(VOID) {}

  void OnStatusBar(VARIANT_BOOL /*StatusBar*/) {}

  void OnTheaterMode(VARIANT_BOOL /*TheaterMode*/) {}

  void OnToolBar(VARIANT_BOOL /*ToolBar*/) {}

  void OnVisible(VARIANT_BOOL /*Visible*/) {::MessageBox(0, "OnVisible", 0, 0);}

  void PrintTemplateInstantiation(IDispatch* /*pDisp*/) {}

  void PrintTemplateTeardown(IDispatch* /*pDisp*/) {}

  void PrivacyImpactedStateChange(VARIANT_BOOL /*PrivacyImpacted*/) {}

  void ProgressChange(long /*Progress*/, long /*ProgressMax*/) {}

  void PropertyChange(BSTR /*szProperty*/) {}

  void SetSecureLockIcon(long /*SecureLockIcon*/) {}

  void StatusTextChange(BSTR /*Text*/) {}

  void TitleChange(BSTR /*Text*/) {}

  void WindowClosing(VARIANT_BOOL /*IsChildWindow*/, VARIANT_BOOL* /*Cancel*/) {}

  void WindowSetHeight(long /*Height*/) {}

  void WindowSetLeft(long /*Left*/) {}

  void WindowSetResizable(VARIANT_BOOL /*Resizable*/) {}

  void WindowSetTop(long /*Top*/) {}

  void WindowSetWidth(long /*Width*/) {}

  HRESULT STDMETHODCALLTYPE GetTypeInfoCount(unsigned int FAR*  pctinfo) {
    MUST_BE_IMPLEMENTED("GetTypeInfoCount")
    *pctinfo = 0;
    return S_OK;
  }

  HRESULT STDMETHODCALLTYPE GetTypeInfo( 
    unsigned int         /*iTInfo*/,         
    LCID                 /*lcid  */,                   
    ITypeInfo FAR* FAR*  /*ppTInfo*/  
  ) {
    MUST_BE_IMPLEMENTED("GetTypeInfo")
  }

  HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
    REFIID             /*riid*/,                  
    OLECHAR FAR* FAR*  /*rgszNames*/,  
    unsigned int       /*cNames*/,          
    LCID               /*lcid*/,                   
    DISPID       FAR*  /*rgDispId*/
) {
   MUST_BE_IMPLEMENTED("GetIDsOfNames")
}

  HRESULT STDMETHODCALLTYPE Invoke( 
    DISPID             dispIdMember,      
    REFIID             riid,              
    LCID               lcid,                
    WORD               /*wFlags      */,
    DISPPARAMS   FAR*  /*pDispParams */,
    VARIANT      FAR*  /*pVarResult  */,
    EXCEPINFO    FAR*  /*pExcepInfo  */,
    unsigned int FAR*  /*puArgErr    */
    );

  protected:

    // If false is returned, the navigation is canceled.
    // Returning true proceeds.
    virtual bool BeforeNavigate(std::string const&) {return true;}; 
};

#endif
