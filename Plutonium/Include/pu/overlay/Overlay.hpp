
/*

    Plutonium library

    @file Overlay.hpp
    @brief TODO...
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/Container.hpp>

namespace pu::overlay
{
    class Overlay : public Container
    {
        public:
            Overlay(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, draw::Color Background, bool Rounded = true);
            ~Overlay();
            void SetRadius(uint32_t Radius);
            uint32_t GetRadius();
            virtual void OnPreRender(render::Renderer *Drawer);
            virtual void OnPostRender(render::Renderer *Drawer);
            bool Render(render::Renderer *Drawer);
            void NotifyEnding(bool End);
        private:
            int32_t fadea;
            draw::Color bg;
            uint32_t rad;
            bool end;
            bool round;
    };
}