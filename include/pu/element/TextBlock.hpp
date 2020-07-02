
/*

    Plutonium library

    @file TextBlock.hpp
    @brief A TextBlock is a very useful Element which is used to draw text on the screen.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>

namespace pu::element
{
    class TextBlock : public Element
    {
        public:
            TextBlock(uint32_t X, uint32_t Y, std::string Text, uint32_t FontSize = 25);
            ~TextBlock();
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            uint32_t GetHeight();
            uint32_t GetTextWidth();
            uint32_t GetTextHeight();
            std::string GetText();
            void SetText(std::string Text);
            void SetFont(render::NativeFont Font);
			void SetFont(std::string Font, uint32_t Size);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            std::string text;
            uint32_t x;
            uint32_t y;
            render::NativeFont fnt;
            uint32_t fsize;
            draw::Color clr;
            render::NativeTexture ntex;
    };
}
