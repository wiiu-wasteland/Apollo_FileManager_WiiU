
/*

    Plutonium library

    @file Button.hpp
    @brief A Button is an Element for option selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <functional>
#include <pu/element/Element.hpp>

namespace pu::element
{
    class Button : public Element
    {
        public:
            Button(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, std::string Content, draw::Color TextColor, draw::Color Color, uint32_t fontSize = 25);
            ~Button();
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            void SetWidth(uint32_t Width);
            uint32_t GetHeight();
            void SetHeight(uint32_t Height);
            std::string GetContent();
            void SetContent(std::string Content);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            void SetContentFont(render::NativeFont Font);
            void SetOnClick(std::function<void()> ClickCallback);
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
            render::NativeFont fnt;
            draw::Color clr;
            std::string cnt;
            std::function<void()> clickcb;
            bool hover;
            int32_t hoverfact;
            render::NativeTexture ntex;
    };
}
