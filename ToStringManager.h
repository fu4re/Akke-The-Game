#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename data>
std::string toStirng(const data& value);

#include</GameDev/Akke The Game/Akke The Game/Utilities/ToStringManager.inl> //inline файл с определением ф-ции toString
#endif // !STRINGHELPER_H

