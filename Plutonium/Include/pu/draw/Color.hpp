
/*

    Plutonium library

    @file Color.hpp
    @brief A Color is used for basic RGBA drawing in all kind of elements.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <cstdint>

namespace pu::draw
{
    struct Color
    {
        Color();
        Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A);
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    };
}
