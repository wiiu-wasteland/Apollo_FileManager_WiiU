
/*

    Plutonium library

    @file Rectangle.hpp
    @brief A Rectangle is an Element which simply draws a filled rectangle.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>

namespace pu::element
{
    class Rectangle : public Element
    {
        public:
            Rectangle(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, draw::Color RecColor, uint32_t BorderRadius = 0);
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            void SetWidth(uint32_t Width);
            uint32_t GetHeight();
            void SetHeight(uint32_t Height);
            uint32_t GetBorderRadius();
            void SetBorderRadius(uint32_t Radius);
            draw::Color GetColor();
            void SetColor(draw::Color RecColor);
			void SetDrawSideShadow(bool drawSideShadow, uint32_t sideShadowWidth = 5, uint32_t sideShadowMainAlpha = 160);
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            uint32_t borderr;
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
            draw::Color clr;
			bool drawSideShadow;
			uint32_t sideShadowWidth;
			uint32_t sideShadowMainAlpha;
    };
}
