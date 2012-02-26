g++ -I.. ..\socket.cpp client.cpp  -lWs2_32 -oclient.exe

g++ -I.. ..\socket.cpp EchoServer.cpp  -lWs2_32 -oEchoServer.exe

g++ -I.. -I..\..\misc ..\socket.cpp Proxy.cpp ..\..\misc\Chameleon.cpp -lWs2_32 -oProxy.exe

g++ -I.. ..\socket.cpp MessageDistributor.cpp -lWs2_32 -oMessageDistributor.exe
