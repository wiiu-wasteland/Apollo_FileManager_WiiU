#include <pu/render/SDL2.hpp>
#include <pu/render/Renderer.hpp>

namespace pu::render
{
    NativeTexture ConvertToTexture(NativeSurface Surface)
    {
        NativeTexture tex = SDL_CreateTextureFromSurface(GetMainRenderer(), Surface);
        SDL_FreeSurface(Surface);
        return tex;
    }

    NativeTexture RenderText(NativeFont Font, std::string Text, draw::Color Color)
    {
        NativeSurface txsrf = TTF_RenderUTF8_Blended_Wrapped(Font, Text.c_str(), { Color.R, Color.G, Color.B, Color.A }, 1280);
        SDL_SetSurfaceAlphaMod(txsrf, 255);
        return ConvertToTexture(txsrf);
    }

    NativeTexture LoadImage(std::string Path)
    {
        return ConvertToTexture(IMG_Load(Path.c_str()));
    }

    NativeFont LoadStandardFont(uint32_t Size)
    {
		return LoadFont("romfs:/Fonts/SourceSansPro-Regular.ttf", Size);
    }

    NativeFont LoadFont(std::string Path, uint32_t Size)
    {
        return TTF_OpenFont(Path.c_str(), Size);
    }

    uint32_t GetTextureWidth(NativeTexture Texture)
    {
        int w = 0;
        SDL_QueryTexture(Texture, NULL, NULL, &w, NULL);
        return (uint32_t)w;
    }

    uint32_t GetTextureHeight(NativeTexture Texture)
    {
        int h = 0;
        SDL_QueryTexture(Texture, NULL, NULL, NULL, &h);
        return (uint32_t)h;
    }

    uint32_t GetTextWidth(NativeFont Font, std::string Text)
    {
        int tw = 0;
        TTF_SizeUTF8(Font, Text.c_str(), &tw, NULL);
        return (uint32_t)tw;
    }

    uint32_t GetTextHeight(NativeFont Font, std::string Text)
    {
        int th = 0;
        TTF_SizeUTF8(Font, Text.c_str(), NULL, &th);
        return (uint32_t)th;
    }

    void SetAlphaValue(NativeTexture Texture, uint8_t Alpha)
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(Texture, Alpha);
    }

    void DeleteFont(NativeFont Font)
    {
        TTF_CloseFont(Font);
        Font = NULL;
    }

    void DeleteTexture(NativeTexture Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
    }
}
