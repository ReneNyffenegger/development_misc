#ifndef CONFIG_FILE_H__
#define CONFIG_FILE_H__

#include <string>
#include <map>
#include <vector>

//#include "Chameleon.h"

class ConfigFile {
    std::map   <std::string, std::string> content_;
    std::vector<std::string>              sections_;
public:
    ConfigFile(std::string const& configFile);
    
    std::vector<std::string> GetSections();

    std::string const& Value(std::string const& section, std::string const& entry) const;

//  std::string const& Value(std::string const& section, std::string const& entry, double value);
    std::string const& Value(std::string const& section, std::string const& entry, std::string const& value);

//  Chameleon const& Value(std::string const& section, std::string const& entry) const;

//  Chameleon const& Value(std::string const& section, std::string const& entry, double value);
//  Chameleon const& Value(std::string const& section, std::string const& entry, std::string const& value);
};

#endif 
