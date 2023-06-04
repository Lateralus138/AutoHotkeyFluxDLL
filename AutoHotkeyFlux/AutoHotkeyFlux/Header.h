#pragma once
#include <Windows.h>
#include <string>
#ifndef HEADER_H
#define HEADER_H
extern "C" __declspec(dllexport) LPCWSTR nps_copyright();
extern "C" __declspec(dllexport) LPCWSTR timestamp(unsigned int type);
extern "C" __declspec(dllexport)
LPCWSTR decimal_to_hexadecimal(unsigned int decimal, unsigned int padding, LPCWSTR prefix, bool upper);
extern "C" __declspec(dllexport)
LPCWSTR hexadecimal_color_string_to_int_string(LPCWSTR str, LPCWSTR delim);
#else
extern "C" __declspec(dllimport) LPCWSTR nps_copyright();
extern "C" __declspec(dllimport) LPCWSTR timestamp(unsigned int type);
extern "C" __declspec(dllimport)
LPCWSTR decimal_to_hexadecimal(unsigned int decimal, unsigned int padding, LPCWSTR prefix, bool upper);
extern "C" __declspec(dllexport)
LPCWSTR hexadecimal_color_string_to_int_string(LPCWSTR str, LPCWSTR delim);
#endif