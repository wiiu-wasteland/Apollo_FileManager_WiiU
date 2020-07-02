    
#pragma once
#include <string>
#include <cstdint>
#include <pu/draw.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

namespace pu::render
{
    typedef SDL_Window *NativeWindow;
    typedef SDL_Renderer *NativeRenderer;
    typedef SDL_Surface *NativeSurface;
    typedef SDL_Texture *NativeTexture;
    typedef TTF_Font *NativeFont;

    NativeTexture ConvertToTexture(NativeSurface Surface);
    NativeTexture RenderText(NativeFont Font, std::string Text, draw::Color Color);
    NativeTexture LoadImage(std::string Path);
    NativeFont LoadStandardFont(uint32_t Size);
    NativeFont LoadFont(std::string Path, uint32_t Size);
    uint32_t GetTextureWidth(NativeTexture Texture);
    uint32_t GetTextureHeight(NativeTexture Texture);
    uint32_t GetTextWidth(NativeFont Font, std::string Text);
    uint32_t GetTextHeight(NativeFont Font, std::string Text);
    void SetAlphaValue(NativeTexture Texture, uint8_t Alpha);
    void DeleteFont(NativeFont Font);
    void DeleteTexture(NativeTexture Texture);
}
