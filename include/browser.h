#pragma once
#include <iostream>
#include <vector>
#include "common.h"

extern std::string currentPath;
extern std::vector<File> currentFiles;

class Browser
{
    public:
        Browser();
        ~Browser();
        void LoadFiles(const std::string &_pathname);
        void Open();
        void OpenFile();
        void Refresh();
        void NavigateBack();
        void SelectFile();
        void RenameFile();
        void RemoveFiles();
        void CopyFiles();
        void MoveFiles();
        void PasteFiles();
        void ChangeSortType(SortType _sorttype);
        uint32_t GetNumberOfSelected();
        uint32_t GetClipboardSize();

        std::string GetFileName();
        std::string GetFilePath();
        std::string GetFilePathName();
        std::string GetFilePermissions();
        std::string GetFileExtension();
        uint32_t GetFilesSize();
        bool GetFileType();
        std::pair<uint32_t, uint32_t> CountMultipleFilesType(); // first - number of files, second - number of dirs

    private:
        File firstSelected;
        uint32_t numberOfSelected = 0;
        bool moveFlag = 0; // 0 - copy, 1 - cut
        bool emptyDir = false;
        SortType sortType = SortType::Alphabetical;
        std::string currentPath = SDCARD_PATH;
        std::vector<File> currentFiles;
        std::vector<ClipboardNode> clipboard;
        std::vector<uint32_t> lastCursorPosition;
        std::vector<uint32_t> lastScrollPosition;
        inline void CopyFileOrDir(std::string _source, std::string _dest, bool _type);
        inline void CopyFileOrDirOverwrite(std::string _source, std::string _dest, bool _type, bool _moveflag);
};
