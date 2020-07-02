
/*

    Plutonium library

    @file Menu.hpp
    @brief A Menu is a very useful Element for option browsing or selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>
#include <pu/input/Input.hpp>
#include <vector>
#include <functional>
#include <chrono>

namespace pu::element
{
    class MenuItem
    {
        public:
            MenuItem(std::string Name, std::string SecondName = "");
            ~MenuItem();
            std::string GetName();
			std::string GetSecondName();
            void SetName(std::string Name);
			void SetSecondName(std::string SecondName);
			void SetSecondNameColor(draw::Color Color);
            draw::Color GetColor();
			draw::Color GetSecondNameColor();
            void SetColor(draw::Color Color);
            void AddOnClick(std::function<void()> Callback, uint32_t Key = BUTTON_A);
            uint32_t GetCallbackCount();
            std::function<void()> GetCallback(uint32_t Index);
            uint32_t GetCallbackKey(uint32_t Index);
            std::string GetIcon();
            void SetIcon(std::string Icon);
            bool HasIcon();
            render::NativeFont GetFont();
			render::NativeFont GetSecondFont();
            render::NativeTexture GetNameTexture();
			render::NativeTexture GetSecondNameTexture();
            render::NativeTexture GetIconTexture();
			void SetNameFont(std::string Font, uint32_t Size = 25);
			void SetSecondNameFont(std::string Font, uint32_t Size = 20);
        private:
            std::string name;
			std::string secondname;
            draw::Color clr;
			draw::Color snclr;
            bool hasicon;
            std::string icon;
            std::vector<std::function<void()>> cbs;
            std::vector<uint32_t> cbipts;
            render::NativeFont font;
			render::NativeFont secondfont;
            render::NativeTexture itex;
            render::NativeTexture ntex;
			render::NativeTexture sntex;
    };

    class Menu : public Element
    {
        public:
            Menu(uint32_t X, uint32_t Y, uint32_t Width, draw::Color OptionColor, uint32_t ItemSize, uint32_t ItemsToShow);
            ~Menu();
            uint32_t GetX();
            void SetX(uint32_t X);
            uint32_t GetY();
            void SetY(uint32_t Y);
            uint32_t GetWidth();
            void SetWidth(uint32_t Width);
            uint32_t GetHeight();
            uint32_t GetItemSize();
            void SetItemSize(uint32_t ItemSize);
            uint32_t GetNumberOfItemsToShow();
            void SetNumberOfItemsToShow(uint32_t ItemsToShow);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            draw::Color GetOnFocusColor();
            void SetOnFocusColor(draw::Color Color);
            draw::Color GetScrollbarColor();
            void SetScrollbarColor(draw::Color Color);
            void SetOnSelectionChanged(std::function<void()> Callback);
            void AddItem(MenuItem *Item);
            void ClearItems();
            void SetCooldownEnabled(bool Cooldown);
            MenuItem *GetSelectedItem();
            uint32_t GetSelectedIndex();
			uint32_t GetScrollIndex();
            void SetSelectedIndex(uint32_t Index);
			void SetScrollIndex(uint32_t Scroll);
            void OnRender(render::Renderer *Drawer);
            void OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus);
			void SetDrawShadow(bool drawShadow);
			void SetOnFocus(bool onFocus);
			void SetIconScale(double Scale);
			void SetIconOnly(bool iconOnly);
			double GetIconScale();
			bool IsIconOnly();
			void SetScrollbarPosition(uint32_t scbpos);
			void SetScrollbarWidth(uint32_t scbwidth);
			void SetSecondNamePositionPercent(double Percent);
        private:
            bool dtouch;
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t isize;
            uint32_t ishow;
            uint32_t previsel;
            uint32_t fisel;
            uint32_t isel;
            int32_t pselfact;
            int32_t selfact;
            draw::Color scb;
            draw::Color clr;
            draw::Color fcs;
            bool icdown;
            std::function<void()> onselch;
            std::vector<MenuItem*> itms;
            bool uptime;
            bool uphold;
            std::chrono::time_point<std::chrono::steady_clock> uptp;
            bool downtime;
            bool downhold;
            std::chrono::time_point<std::chrono::steady_clock> downtp;
			bool drawShadow;
			bool onFocus;
			bool iconOnly;
			double iconScale;
			uint32_t scbpos;
			uint32_t scbwidth;
			double snposper;
    };
}
