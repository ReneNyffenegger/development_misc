#include "ConfigFile.h"

#include <fstream>

std::string trim(std::string const& source, char const* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

ConfigFile::ConfigFile(std::string const& configFile) {
  std::ifstream file(configFile.c_str());

  std::string line;
  std::string name;
  std::string value;
  std::string inSection;
  int posEqual;
  while (std::getline(file,line)) {

    if (! line.length()) continue;

    if (line[0] == '#') continue;
    if (line[0] == ';') continue;

    if (line[0] == '[') {
      inSection=trim(line.substr(1,line.find(']')-1));
            sections_.push_back(inSection);
      continue;
    }

    posEqual=line.find('=');
    name  = trim(line.substr(0,posEqual));
    value = trim(line.substr(posEqual+1));

    content_[inSection+'/'+name]=/*Chameleon(*/value/*)*/;
  }
}

std::vector<std::string> ConfigFile::GetSections() {
    return sections_;
}

/*Chameleon*/ 
std::string const& ConfigFile::Value(std::string const& section, std::string const& entry) const {

  std::map<std::string, std::string/*Chameleon*/>::const_iterator ci = content_.find(section + '/' + entry);

  if (ci == content_.end()) throw "does not exist";

  return ci->second;
}

/*Chameleon*/
//std::string const& ConfigFile::Value(std::string const& section, std::string const& entry, double value) {
//  try {
//    return Value(section, entry);
//  } catch(const char *) {
//    return content_.insert(std::make_pair(section+'/'+entry, /*Chameleon(*/value/*)*/)).first->second;
//  }
//}

/*Chameleon*/
std::string const& ConfigFile::Value(std::string const& section, std::string const& entry, std::string const& value) {
  try {
    return Value(section, entry);
  } catch(const char *) {
    return content_.insert(std::make_pair(section+'/'+entry, /*Chameleon(*/value/*)*/)).first->second;
  }
}
