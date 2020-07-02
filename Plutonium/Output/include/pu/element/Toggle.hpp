
/*

    Plutonium library

    @file Toggle.hpp
    @brief A Toggle is an Element used to switch between two options by toggling the item.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>
#include <pu/input.hpp>

namespace pu::element
{
    class Toggle : public Element
    {
        public:
            Toggle(uint32_t X, uint32_t Y, std::string Content, uint32_t Key, draw::Color Color);
            ~Toggle();
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            uint32_t GetHeight();
            std::string GetContent();
            void SetContent(std::string Content);
            void SetFont(render::NativeFont Font);
            draw::Color GetColor();
            void SetColor(draw::Color General);
            uint32_t GetKey();
            void SetKey(uint32_t Key);
            bool IsChecked();
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            std::string cnt;
            uint32_t x;
            uint32_t y;
            uint32_t key;
            bool checked;
            draw::Color clr;
            render::NativeFont fnt;
            uint32_t fsize;
            int32_t togfact;
            render::NativeTexture ntex;
    };
}
