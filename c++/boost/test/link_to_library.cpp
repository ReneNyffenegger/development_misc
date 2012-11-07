//
//       Adapted from 
//       http://www.boost.org/doc/libs/1_52_0/more/getting_started/windows.html#link-your-program-to-a-boost-library
//
//       Demonstrates linking with a Boost binary library
//
#include <boost/regex.hpp>
#include <iostream>
#include <string>


boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

bool match(std::string const& text, std::string& matched) {
     boost::smatch matches;
 
     if (boost::regex_match(text, matches, pat)) {
         matched = matches[2];
         return true;
     }

     return false;
}

void print_if_matched(std::string const& text) {

     std::string matched;
 
     if (match(text, matched)) {
       std::cout << text << " matched: " << matched << std::endl;
     }
     else {
       std::cout << text << " didn't match" << std::endl;
     }
}

int main() {

    print_if_matched("Subject: Re: Hello");
    print_if_matched("Subject: Aw: Hallo");
    print_if_matched("  Subject: none");

}
