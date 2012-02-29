/* 
   Wnd.h

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

#ifndef WND_H_
#define WND_H_

#include <windows.h>

#include <string>

#include "STD_STR.h"

class Wnd {
  public:
    HWND hwnd_;

    Wnd();
    
    void Create(STD_STR const& className, int x, int y, int w, int h, int styles, STD_STR const& title);

    virtual ~Wnd();
    
    void ClientRect(unsigned int& width, unsigned int& height) const;
    
    void Show(bool b=true) const;

    void Enable(bool b=true) const;

    void Focus() const;
    
    void Refresh() const;

    void DefaultGuiFont();

    // void SetFont(const Font&);
              
    void    Text(const STD_STR&);

    virtual Wnd* Parent() const = 0;

    virtual int  StylesToAddInCreate() const = 0;

    STD_STR Text() const;

    virtual void Move(int x, int y, int width, int height, bool repaint=true);
};

#endif
