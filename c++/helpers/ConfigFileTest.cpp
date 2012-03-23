//
// MinGW:
//
//    g++  ConfigFile.cpp ConfigFileTest.cpp -o ConfigFileTest.exe
//
#include "ConfigFile.h"

#include <iostream>

int main() {
  try {
  ConfigFile cf("config.txt");

  std::string foo;
  std::string water;
  std::string four;
  std::string unknown;

  std::vector<std::string> sections = cf.GetSections();

  for (std::vector<std::string>::iterator i = sections.begin(); i < sections.end(); i++) {
    std::cout<<"Section: " << *i << std::endl;
  }


  foo      = cf.Value("section_1","foo"     , "?");
  water    = cf.Value("section_2","water"   , "?");
  four     = cf.Value("section_2","four"    , "?");
  unknown  = cf.Value("section_3","unknown" , "?");

  std::cout << foo     << std::endl;
  std::cout << water   << std::endl;
  std::cout << four    << std::endl;
  std::cout << unknown << std::endl;

  return 0;
  } 
  catch (const char* e) {
    std::cout << std::string("Exception ") + e;
  }
}
