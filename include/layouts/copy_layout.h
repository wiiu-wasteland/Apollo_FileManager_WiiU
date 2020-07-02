#pragma once
#include "common.h"

namespace ui
{
    class CopyLayout : public pu::Layout
    {
        public:
            CopyLayout();
            ~CopyLayout();
            void Start(uint32_t _value, bool _moveFlag);
            void Update(const std::string &_from, const std::string &_to);
            void Finish();
            void FinishUpdate(std::string _item);
            void Reset();

        private:
            std::string action = "";
            std::string item = "";
            uint32_t numberOfElements = 0;
            uint32_t numberOfElementsDone = 0;
            pu::element::TextBlock *copyTextHeader;
            pu::element::TextBlock *copyTextFrom;
            pu::element::TextBlock *copyTextTo;
            pu::element::ProgressBar *copyProgressBar;
    };
}
