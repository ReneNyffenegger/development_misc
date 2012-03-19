# Some C++ classes to for MSHTML

I was able to compile **MSHTMLTest.exe** and **DisplayHTML.exe** with [this makefile](https://raw.github.com/ReneNyffenegger/development_misc/master/windows/mshtml/makefile) and MinGW.
Note that it also uses some source code outside this directory (but within this GitHub repository).

The file **mshtmhst.h** was downloaded from [this link](http://www.koders.com/cpp/fidECEAB5019B72637F91A5DB3A87FB47965888F9FF.aspx) because MinGW doesn't seem to come with it.
 
## MSHTMLTest.exe 

This .exe simply shows the content of the HTML that is defined in [MSHTMLTest.cpp](https://raw.github.com/ReneNyffenegger/development_misc/master/windows/mshtml/MSHTMLTest.cpp)

## DisplayHTML.exe

DisplayHTML.exe can be called from the command line (that is most probably `cmd.exe`) either like so

    c:\>DisplayHTML.exe  www.some-url.yz

or (in order to show a local html-file)

    c:\>DisplayHTML.exe  file://c:/path/to/some/file.html
