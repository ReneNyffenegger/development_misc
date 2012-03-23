#C++ Helpers

##ConfigFile

[Originally](http://www.adp-gmbh.ch/cpp/config_file.html), the idea was to parse a [config file](https://raw.github.com/ReneNyffenegger/development_misc/master/c++/helpers/config.txt) along
with [Chameleon.cpp](https://raw.github.com/ReneNyffenegger/development_misc/master/c++/misc/Chameleon.cpp) so that the values in the config
file can be assigned to `double` and to `std::string`

   ConfigFile cf("configFile.txt");

   double      d = cf.Value (...);
   std::string s = cf.Value (...);

However, this approach caused more problems than it solved. Therefore, I decided to forego `Chameleon`. The class can now only be used to return `std::strings`.

###Thanks

Thanks to *W. Vaebris* who improved the class.

##Tracer

TODO: Description.

##UrlHelper

TODO: Description.
