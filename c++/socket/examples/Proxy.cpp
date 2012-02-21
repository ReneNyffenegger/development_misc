/* 
   Proxy.cpp

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

#include "Socket.h"

#include <iostream>
#include <process.h>
#include <sstream>

int         portProxy;
std::string addrServer;
int         portServer;

unsigned __stdcall RunProxyThread (void* a) {
  Socket*      s = (Socket*) a;
  SocketClient c(addrServer, portServer);

  while (1) {
    SocketSelect sel(s, &c);

    bool still_connected = true;

    if (sel.Readable(s)) {
      std::string bytes = s->ReceiveBytes();
      c.SendBytes(bytes);
      std::cout << "Server: " << bytes << std::endl;
      if (bytes.empty()) still_connected=false;
    }
    if (sel.Readable(&c)) {
      std::string bytes = c.ReceiveBytes();
      s->SendBytes(bytes);
      std::cout << "Client: " << bytes << std::endl;
      if (bytes.empty()) still_connected=false;
    }
    if (! still_connected) {
      break;
    }
  }

  delete s;

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Usage:" << std::endl;
    std::cout << "  proxy <port proxy> <addr server> <port server>" << std::endl;
    std::cout << std::endl;
    std::cout << "  This proxy will then listen on <port proxy> and whenever it receives" << std::endl;
    std::cout << "  a connection, relays the traffic to the <port server> of <addr server>." << std::endl;
    std::cout << "  This makes it ideal to see what an SMTP Client exchanges with a SMTP Server," << std::endl;
    std::cout << "  or equally what a NNTP client exchanges with an NNTP Server." << std::endl << std::endl;
    return -1;
  }

  std::stringstream s; 
  
  s<<argv[1]; s>>portProxy; s.clear();

  addrServer=argv[2];

  s<<argv[3]; s>>portServer;

  SocketServer in(portProxy,5);

  while (1) {
    Socket* s=in.Accept();

    unsigned ret;
    _beginthreadex(0, 0, RunProxyThread,(void*) s,0,&ret);
  }
  
  return 0;
}
