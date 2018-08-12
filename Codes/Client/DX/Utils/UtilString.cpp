#include "PCH.h"
#include "UtilString.h"
#include <locale>
#include <codecvt>

using namespace Utils;

std::string UtilString::ToAscii(const std::wstring& s)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(s);
}

std::wstring UtilString::ToUnicode(const std::string& s)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(s);
}

std::vector<std::string>& UtilString::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> UtilString::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    UtilString::split(s, delim, elems);
    return elems;
}