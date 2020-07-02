#pragma once
#define SDCARD_PATH "fs:/vol/external01"
#include <iostream>
#include <vector>
#include <pu/Plutonium>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/crash.h>

struct File
{
    std::string pathname;
    std::string name;
    std::string path;
    bool type; // 0 - file, 1 - dir
    uint32_t size;
    std::string extension;
    bool selected = false;

    File(std::string _pn = "", std::string _n = "", std::string _p = "", bool _t = 0, uint32_t _s = 0, std::string _x = "")
    : pathname(_pn),
      name(_n),
      path(_p),
      type(_t),
      size(_s),
      extension(_x)
    {
    }
};

/*
// pathname - sdmc:/switch/text.txt
// name - text.txt
// path - sdmc:/switch/
*/

struct ClipboardNode
{
    std::string base;
    std::string path;
    bool directory;
    int overwrite;

    ClipboardNode(std::string _b = "", std::string _p = "", bool _d = 0, int _o = 0)
    : base(_b),
      path(_p),
      directory(_d), // to do: change it to "type"
      overwrite(_o) // 0 - don't overwrite, 1 - overwrite, 2 - inform that cannot overwrite
    {
    }
};

enum SortType
{
    Alphabetical = 0,
    Alphabetical_Reversed = 1,
    By_Size = 2,
    By_Size_Reversed = 3
};
