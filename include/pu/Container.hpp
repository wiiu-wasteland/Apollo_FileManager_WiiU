
/*

    Plutonium library

    @file Container.hpp
    @brief A Container is a basic object which contains a bunch of Elements.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element.hpp>
#include <vector>

namespace pu
{
    class Container
    {
        public:
            Container(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height);
            void Add(element::Element *Elm);
            element::Element *At(uint32_t Index);
            bool Has(element::Element *Elm);
            void Clear();
            uint32_t GetCount();
            void SetX(uint32_t X);
            uint32_t GetX();
            void SetY(uint32_t Y);
            uint32_t GetY();
            void SetWidth(uint32_t Width);
            uint32_t GetWidth();
            void SetHeight(uint32_t Height);
            uint32_t GetHeight();
            void PreRender();
        protected:
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
            std::vector<element::Element*> elms;
    };
}