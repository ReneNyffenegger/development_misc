CC_FLAGS_AND_OPTS=-I. -I../helpers -I.. -I../../c++/helpers -Wall -c $(CC_ENV_OPTS)

LIB_PATH=c:/tools/mingw/lib

all: MSHTMLTest.exe DisplayHTML.exe

MSHTMLTest.exe : o/MSHTMLTest.o o/HTMLWindow.o o/OleClientSite.o o/OleInPlaceSite.o o/DocHostUiHandler.o o/Tracer.o o/VariantHelper.o o/UrlHelper.o o/stdHelpers.o o/win32_Unicode.o
	g++ -mwindows  o/HTMLWindow.o o/OleClientSite.o o/OleInPlaceSite.o o/DocHostUiHandler.o o/Tracer.o o/VariantHelper.o o/UrlHelper.o o/MSHTMLTest.o o/stdHelpers.o o/win32_Unicode.o -oMSHTMLTest.exe -luuid -loleaut32 -lole32 
	strip  MSHTMLTest.exe

DisplayHTML.exe : o/DisplayHTML.o o/HTMLWindow.o o/OleClientSite.o o/OleInPlaceSite.o o/DocHostUiHandler.o o/Tracer.o o/VariantHelper.o o/UrlHelper.o o/stdHelpers.o
	g++ -mwindows  o/HTMLWindow.o o/OleClientSite.o o/OleInPlaceSite.o o/DocHostUiHandler.o o/Tracer.o o/VariantHelper.o o/UrlHelper.o o/DisplayHTML.o o/stdHelpers.o o/win32_Unicode.o -oDisplayHTML.exe -luuid -loleaut32 -lole32
	strip  DisplayHTML.exe

o/MSHTMLTest.o : MSHTMLTest.cpp 
	g++ $(CC_FLAGS_AND_OPTS) MSHTMLTest.cpp -o o/MSHTMLTest.o

o/DisplayHTML.o : DisplayHTML.cpp 
	g++ $(CC_FLAGS_AND_OPTS) DisplayHTML.cpp -o o/DisplayHTML.o

o/HTMLWindow.o : HTMLWindow.cpp 
	g++ $(CC_FLAGS_AND_OPTS) HTMLWindow.cpp -o o/HTMLWindow.o

o/OleClientSite.o : OleClientSite.cpp OleClientSite.h
	g++ $(CC_FLAGS_AND_OPTS) OleClientSite.cpp -o o/OleClientSite.o

o/OleInPlaceSite.o : OleInPlaceSite.cpp OleInPlaceSite.h
	g++ $(CC_FLAGS_AND_OPTS) OleInPlaceSite.cpp -o o/OleInPlaceSite.o

o/DocHostUiHandler.o : DocHostUiHandler.cpp DocHostUiHandler.h
	g++ $(CC_FLAGS_AND_OPTS) DocHostUiHandler.cpp -o o/DocHostUiHandler.o

o/Tracer.o : ../../c++/helpers/Tracer.cpp ../../c++/helpers/Tracer.h
	g++ $(CC_FLAGS_AND_OPTS) ../../c++/helpers/Tracer.cpp -o o/Tracer.o

o/VariantHelper.o : ../helpers/VariantHelper.cpp ../helpers/VariantHelper.h
	g++ $(CC_FLAGS_AND_OPTS) ../helpers/VariantHelper.cpp -o o/VariantHelper.o

o/UrlHelper.o : ../../c++/helpers/UrlHelper.cpp ../../c++/helpers/UrlHelper.h
	g++ $(CC_FLAGS_AND_OPTS) ../../c++/helpers/UrlHelper.cpp -o o/UrlHelper.o

o/stdHelpers.o : ../../c++/helpers/stdHelpers.cpp ../../c++/helpers/stdHelpers.h
	g++ $(CC_FLAGS_AND_OPTS) ../../c++/helpers/stdHelpers.cpp -o o/stdHelpers.o

o/win32_Unicode.o : ../win32_Unicode.cpp ../win32_Unicode.h
	g++ $(CC_FLAGS_AND_OPTS) ../win32_Unicode.cpp -o o/win32_Unicode.o

clean:
	rm *.exe o/*.o
