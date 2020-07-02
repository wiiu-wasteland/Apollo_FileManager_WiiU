
/*

    Plutonium library

    @file Dialog.hpp
    @brief A Dialog is an easy way to ask the user to choose between several options.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/render.hpp>
#include <vector>

namespace pu
{
    class Dialog
    {
        public:
            Dialog(std::string Title, std::string Content);
            ~Dialog();
            void AddOption(std::string Name);
            void SetCancelOption(std::string Name = "Cancel");
            void RemoveCancelOption();
            bool HasCancelOption();
            void SetIcon(std::string Icon);
            bool Hasicon();
            uint32_t Show(render::Renderer *Drawer, void *App);
            bool UserCancelled();
            bool IsOk();
        private:
            bool hcancel;
            std::string scancel;
            render::NativeFont tfont;
            render::NativeFont cfont;
            render::NativeFont ofont;
            render::NativeTexture title;
            render::NativeTexture cnt;
            std::vector<std::string> sopts;
            std::vector<render::NativeTexture> opts;
            uint32_t osel;
            bool cancel;
            bool hicon;
            render::NativeTexture icon;
            uint32_t prevosel;
            int32_t pselfact;
            int32_t selfact;
    };
}