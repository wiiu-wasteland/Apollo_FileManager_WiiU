
/*

    Plutonium library

    @file Image.hpp
    @brief An Image is an Element showing a picture. (JPEG, PNG, TGA, BMP)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>

namespace pu::element
{
    class Image : public Element
    {
        public:
            Image(uint32_t X, uint32_t Y, std::string Image);
            ~Image();
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            void SetWidth(uint32_t Width);
            uint32_t GetHeight();
            void SetHeight(uint32_t Height);
            std::string GetImage();
            void SetImage(std::string Image);
            bool IsImageValid();
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
        private:
            std::string img;
            render::NativeTexture ntex;
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
    };
}
