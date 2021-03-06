#include <string>
#include <vpad/input.h>
#include "utils.h"
#include "app.h"
#include "fs.h"

extern MainApplication *app;

void SortFiles(std::vector<File> &_files, SortType _sorttype)
{
    switch (_sorttype)
    {
        default:
        case SortType::Alphabetical:
            std::sort(_files.begin(), _files.end(), CompareNames);
        break;

        case SortType::Alphabetical_Reversed:
            std::sort(_files.rbegin(), _files.rend(), CompareNamesReversed);
        break;

        case SortType::By_Size:
        {
            SortFiles(_files, SortType::Alphabetical);

            std::vector<File>::iterator iter = _files.end();
            for (std::vector<File>::iterator it = _files.begin(); it != _files.end(); it++)
            {
                if ((*it).type == 0)
                {
                    iter = it;
                    break;
                }
            }
            if (iter != _files.end())
                std::partial_sort(iter, _files.end(), _files.begin(), CompareSizes);
        }
        break;

        case SortType::By_Size_Reversed:
        {
            SortFiles(_files, SortType::Alphabetical);

            std::vector<File>::iterator iter = _files.end();
            for (std::vector<File>::iterator it = _files.begin(); it != _files.end(); it++)
            {
                if ((*it).type == 0)
                {
                    iter = it;
                    break;
                }
            }
            if (iter != _files.end())
                std::partial_sort(iter, _files.end(), _files.begin(), CompareSizesReversed);
        }
        break;
    }
}

std::string GetRomFsFileExt(bool _ext)
{
    switch (_ext)
    {
        default:
        case 0:
            return "file";
        break;

        case 1:
            return "dir";
        break;
    }
}

std::string GetRomFsResource(std::string _name, std::string _dir)
{
    return (R"(romfs:/)" + _dir + "/" + _name + R"(.png)");
}

std::string GetRomFsFont(std::string _fullfontname)
{
    return (R"(romfs:/Fonts/)" + _fullfontname);
}

bool CompareNames(File _f, File _g)
{
    std::transform(_f.name.begin(), _f.name.end(), _f.name.begin(), ::tolower);
    std::transform(_g.name.begin(), _g.name.end(), _g.name.begin(), ::tolower);

    switch (_f.type - _g.type)
    {
        default:
        case 0:
            return (_f.name < _g.name);
        break;

        case -1:
            return false;;
        break;

        case 1:
            return true;
        break;
    }
}

bool CompareNamesReversed(File _f, File _g)
{
    std::transform(_f.name.begin(), _f.name.end(), _f.name.begin(), ::tolower);
    std::transform(_g.name.begin(), _g.name.end(), _g.name.begin(), ::tolower);

    switch (_f.type - _g.type)
    {
        default:
        case 0:
            return (_f.name < _g.name);
        break;

        case -1:
            return true;;
        break;

        case 1:
            return false;
        break;
    }
}

bool CompareSizes(File _f, File _g)
{
    return (_f.size < _g.size);
}

bool CompareSizesReversed(File _f, File _g)
{
    return (_f.size > _g.size);
}

std::string FormatSize(uint32_t _size)
{
    const char *sizes[6] = {"B ", "KB", "MB", "GB", "TB", "PB"};
    char sizeout[32] = {0};

    for (int i = 0; i < 5; i++)
    {
        if (_size/pow(1024.00, i) > 1023.5)
            continue;
        else
        {
            std::sprintf(sizeout, "%.2f %s", _size/pow(1024.00, i), sizes[i]);
            break;
        }
    }
    return sizeout;
}

std::string FormatNumber(uint32_t _number)
{
    std::string num = std::to_string(_number);
    int i = num.length() - 3;
    while (i > 0)
    {
        num.insert(i, " ");
        i-=3;
    }
    return num;
}

std::string ShortenText(std::string _text, uint32_t _maxchar, std::string _dots, bool _dotspos) // _dotspos: 0 - left, 1 - right
{
    if (_text.length() > _maxchar)
    {
        if (_dotspos == 0)
        {
            _text.erase(_text.begin(), _text.end()-_maxchar);
            _text.insert(0, _dots);
        }
        else
        {
            _text.erase(_text.begin()+_maxchar, _text.end());
            _text.append(_dots);
        }
    }

    return _text;
}

std::string WrapText(std::string _text, uint32_t _maxchar)
{
    if (_text.length() > _maxchar)
    {
        for (uint32_t i = 0; i < _text.length(); i += _maxchar)
        {
            if (i % _maxchar == 0 && i != 0)
                _text.insert(i-1, "\n");
        }
    }

    return _text;
}

std::vector<std::string> DivideLongText(std::string _text, uint32_t _maxchar)
{
    std::vector<std::string> textcontainer;
    uint32_t startpos = 0;

    if (_text.length() > _maxchar)
    {
        for (uint32_t i = 0; i < _text.length(); i += _maxchar)
        {
            startpos = i;
            textcontainer.push_back(_text.substr(startpos, _maxchar));
        }
    }
    else
    {
        textcontainer.push_back(_text);
    }

    return textcontainer;
}

namespace sys
{
    std::string GetTextFromSoftwareKeyboard(std::string _header, std::string _guide, std::string _initial) // to do: check exception if error
    {
        /*std::string text;
        SwkbdConfig kbd;
        char tmpoutstr[FS_MAX_PATH] = {0};
        Result rc = swkbdCreate(&kbd, 0);

        if (R_SUCCEEDED(rc))
        {
            swkbdConfigMakePresetDefault(&kbd);
            swkbdConfigSetHeaderText(&kbd, _header.c_str());
            swkbdConfigSetGuideText(&kbd, _guide.c_str());
            swkbdConfigSetInitialText(&kbd, _initial.c_str());
            rc = swkbdShow(&kbd, tmpoutstr, sizeof(tmpoutstr));
            if (R_SUCCEEDED(rc))
            {
                text = std::string(tmpoutstr);
            }
        }
        swkbdClose(&kbd);
        return text;*/
		return _initial;
    }

    std::string GetCurrentTime()
    {
        time_t lTime = time(NULL);
        struct tm* timestruct = localtime((const time_t *) &lTime);
        int hour = timestruct->tm_hour;
        int min = timestruct->tm_min;
        int sec = timestruct->tm_sec;
        char time[9];
        std::sprintf(time, "%02d:%02d:%02d", hour, min, sec);
        return time;
    }
    
    static uint32_t batteryPercent[7] = {5, 0, 1, 3, 5, 8, 10};

	void GetBatteryStatus(uint32_t &level, bool &charging)
	{
		VPADReadError error;
		VPADStatus status;
		VPADRead(VPAD_CHAN_0, &status, 1, &error);
		level = batteryPercent[status.battery % 7];
		charging = status.battery == 0;
    }
}
