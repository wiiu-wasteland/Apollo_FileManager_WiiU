#pragma once
#include "common.h"

namespace ui
{
    class MainLayout : public pu::Layout
    {
        public:
            MainLayout();
            ~MainLayout();
            void LoadItems(std::vector<File> &files);
            uint32_t GetSelectedIndex();
            uint32_t GetScrollIndex();
            bool IsEmptyDirTextShown();
            void SetCursorPosition(uint32_t _cursor, uint32_t _scroll);
            void SetMenuElementIndexColor(pu::draw::Color _color);
            void SetLocationBarText(std::string _text);
            void OpenAction();
            void SetOnFocus(bool _focus);

        private:
            pu::element::TextBlock *emptyDirText;
            pu::element::Menu *filesMenu;

            // location bar
            pu::element::TextBlock *locationText;
            pu::element::Image *locationIcon;

            // to do: remember user choice of sorttype
            SortType sortType = SortType::Alphabetical;
            int ItemsToShow = 8;
    };
}
