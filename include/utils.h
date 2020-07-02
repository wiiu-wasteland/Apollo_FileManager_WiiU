#pragma once
#include "common.h"

void SortFiles(std::vector<File> &_files, SortType _sorttype);
std::string GetRomFsFileExt(bool _ext);
std::string GetRomFsResource(std::string _name, std::string _dir = "Common");
std::string GetRomFsFont(std::string _fullfontname);
bool CompareNames(File _f, File _g);
bool CompareNamesReversed(File _f, File _g);
bool CompareSizes(File _f, File _g);
bool CompareSizesReversed(File _f, File _g);
std::string FormatSize(uint32_t _size);
std::string FormatNumber(uint32_t _number);
std::string ShortenText(std::string _text, uint32_t _maxchar, std::string _dots = "", bool _dotspos = 0); // _dotspos: 0 - left, 1 - right
std::string WrapText(std::string _text, uint32_t _maxchar);
std::vector<std::string> DivideLongText(std::string _text, uint32_t _maxchar);

namespace sys
{
    std::string GetTextFromSoftwareKeyboard(std::string _header = "", std::string _guide = "", std::string _initial = "");
    std::string GetCurrentTime();
    uint32_t GetBatteryLevel();
	void GetBatteryStatus(uint32_t &level, bool &charging);
}
