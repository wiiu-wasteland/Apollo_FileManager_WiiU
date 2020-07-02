
/*

    Plutonium library

    @file Renderer.hpp
    @brief A Renderer is the object performing basic rendering. (simply, a SDL2 wrapper)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/draw.hpp>
#include <pu/render/SDL2.hpp>
#include <string>
#include <fstream>
#include <romfs-wiiu.h>

namespace pu::render
{
    class Renderer
    {
        public:
            void Initialize();
            void Finalize();
            bool HasInitialized();
            bool HasRomFs();
            void InitializeRender(draw::Color Color);
            void FinalizeRender();
            void RenderTexture(NativeTexture Texture, uint32_t X, uint32_t Y, int AlphaMod = -1);
            void RenderTextureScaled(NativeTexture Texture, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, int AlphaMod = -1);
            void RenderRectangle(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height);
            void RenderRectangleFill(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height);
            void RenderRoundedRectangle(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, uint32_t Radius);
            void RenderRoundedRectangleFill(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, uint32_t Radius);
            void RenderCircle(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Radius);
            void RenderCircleFill(draw::Color Color, uint32_t X, uint32_t Y, uint32_t Radius);
            void RenderShadowSimple(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, uint32_t BaseAlpha, uint8_t MainAlpha = 255);
			void RenderSideShadowSimple(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, uint32_t BaseAlpha, uint8_t MainAlpha = 255);
            void SetBaseRenderPosition(uint32_t X, uint32_t Y);
            void UnsetBaseRenderPosition();
            void SetBaseRenderAlpha(uint8_t Alpha);
            void UnsetBaseRenderAlpha();
        private:
            bool okromfs;
            bool initialized;
            NativeWindow rendwd;
            NativeSurface rendsf;
            uint32_t basex;
            uint32_t basey;
            int basea;
    };

    NativeRenderer GetMainRenderer();
}
