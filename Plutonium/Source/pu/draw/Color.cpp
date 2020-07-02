#include <pu/draw/Color.hpp>

namespace pu::draw
{
    Color::Color()
    {
        this->R = 0;
        this->G = 0;
        this->B = 0;
        this->A = 255;
    }

    Color::Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
    {
        this->R = R;
        this->G = G;
        this->B = B;
        this->A = A;
    }
}