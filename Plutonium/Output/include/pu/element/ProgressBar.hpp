
/*

    Plutonium library

    @file ProgressBar.hpp
    @brief A ProgressBar is an Element which represents a progress (a percentage) by filling a bar.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>

namespace pu::element
{
    class ProgressBar : public Element
    {
        public:
            ProgressBar(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, double MaxValue);
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            void SetWidth(uint32_t Width);
            uint32_t GetHeight();
            void SetHeight(uint32_t Height);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            draw::Color GetProgressColor();
            void SetProgressColor(draw::Color Color);
            double GetProgress();
            void SetProgress(double Progress);
            void IncrementProgress(double Progress);
            void DecrementProgress(double Progress);
            void SetMaxValue(double Max);
            double GetMaxValue();
            void FillProgress();
            void ClearProgress();
            bool IsCompleted();
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
            double val;
            double maxval;
            draw::Color clr;
            draw::Color oclr;
    };
}
