#include "pch.h"
#include "Header.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include <limits.h>
#include <filesystem>
extern "C" __declspec(dllexport) LPCWSTR nps_copyright()
{
  struct tm newtime;
  __time64_t long_time;
  errno_t err;
  _time64(&long_time);
  err = _localtime64_s(&newtime, &long_time);
  if (err)
  {
    return L"ERROR";
  }
  std::wstringstream wss;
  wss << "© " << (1900 + newtime.tm_year) << " Ian Pride - New Pride Software/Services";
  return wss.str().c_str();
}
extern "C" __declspec(dllexport) LPCWSTR timestamp(unsigned int type = 0)
{
  if (type > 1)
  {
    return L"ERROR";
  }
  SYSTEMTIME st;
  LPCWSTR time_zone = { 0 };
  if (type == 0)
  {
    GetLocalTime(&st);
    DYNAMIC_TIME_ZONE_INFORMATION tzinfo;
    DWORD tzresult = GetDynamicTimeZoneInformation(&tzinfo);
    if ((tzresult == TIME_ZONE_ID_INVALID) || (tzresult == TIME_ZONE_ID_UNKNOWN))
    {
      time_zone = L"(UNKNOWN)";
    }
    else
    {
      time_zone = tzinfo.TimeZoneKeyName;
    }
  }
  else
  {
    GetSystemTime(&st);
    time_zone = L"Universal Time Coordinated";
  }
  std::wstringstream wss;
  std::map<WORD, std::string> days
  {
    { (WORD)0, "Sunday"},
    { (WORD)1, "Monday"},
    { (WORD)2, "Tuesday" },
    { (WORD)3, "Wednesday" },
    { (WORD)4, "Thursday" },
    { (WORD)5, "Friday" },
    { (WORD)6, "Saturday" }
  };
  std::map<WORD, std::string> months
  {
    { (WORD)1, "January" },   { (WORD)2, "February" },  { (WORD)3, "March" },
    { (WORD)4, "April" },     { (WORD)5, "May" },       { (WORD)6, "June" },
    { (WORD)7, "July" },      { (WORD)8, "August" },    { (WORD)9, "September" },
    { (WORD)10, "October" },  { (WORD)11, "November" }, { (WORD)12, "December" }
  };
  wss
    << std::setfill(L'0')
    << std::setw(2) << st.wHour
    << std::setw(1) << L":"
    << std::setw(2) << st.wMinute << L" "
    << days[st.wDay].c_str() << L", "
    << months[st.wMonth].c_str() << L" "
    << st.wDay << L", "
    << st.wYear << " " << time_zone;
  return wss.str().c_str();
}
extern "C" __declspec(dllexport)
LPCWSTR decimal_to_hexadecimal
(
  unsigned int decimal,
  unsigned int padding = 0,
  LPCWSTR prefix = L"",
  bool upper = false)
{
  if ((decimal > UINT_MAX) || (padding > UINT_MAX))
  {
    return L"ERROR";
  }
  std::wstringstream wss, wsst;
  std::wstring dec;
  if (!upper)
  {
    wsst << std::hex << decimal;
    wsst >> dec;
  }
  else
  {
    wsst << std::uppercase << std::hex << decimal;
    wsst >> dec;
  }
  wss << prefix << std::setfill(L'0') << std::setw(padding) << dec;
  return wss.str().c_str();
}
extern "C" __declspec(dllexport)
LPCWSTR hexadecimal_color_string_to_int_string(LPCWSTR str, LPCWSTR delim)
{
  std::wstring wtemp = str;
  int strl = (int)wtemp.length();
  if ((strl < 6) || (strl > 8))
  {
    return L"";
  }
  if (str[0] == L'#')
  {
    wtemp = wtemp.substr(1);
  }
  if ((str[0] == L'0') && (str[1] == L'x'))
  {
    wtemp = wtemp.substr(2);
  }
  std::wstring
    red = wtemp.substr(0, 2),
    green = wtemp.substr(2, 2),
    blue = wtemp.substr(4, 2);
  int rhex = 0, ghex = 0, bhex = 0;
  std::wstringstream ss;
  ss << std::hex << red.c_str(); ss >> rhex;
  ss.str(std::wstring()); ss.clear();
  ss << std::hex << green.c_str(); ss >> ghex;
  ss.str(std::wstring()); ss.clear();
  ss << std::hex << blue.c_str(); ss >> bhex;
  ss.str(std::wstring()); ss.clear();
  ss
    << std::dec << static_cast<int>(rhex) << delim
    << static_cast<int>(ghex) << delim
    << static_cast<int>(bhex);
  return ss.str().c_str();
}