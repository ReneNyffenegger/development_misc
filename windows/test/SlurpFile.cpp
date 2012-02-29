/*
   g++ -Wall SlurpFile.cpp ../win32_SlurpFile.cpp -oSlurpFile.exe

   See http://www.adp-gmbh.ch/win/programming/common/win32_slurpfile.html
*/

#include "win32_SlurpFile.h"
#include <iostream>

int main() {
//  Slurp myself...
    std::string file_content = Win32_SlurpFile("SlurpFile.cpp");

//  ... and print myself:
    std::cout << file_content;
}
