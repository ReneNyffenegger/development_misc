#include <string>
#include <windows.h>

std::string  ws2s(std::wstring const& s);
std::wstring s2ws(std::string const& s, unsigned int codepage=CP_ACP);
