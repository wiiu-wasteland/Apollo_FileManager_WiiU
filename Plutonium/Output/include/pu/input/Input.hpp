
/*

    Plutonium library

    @file Input.hpp
    @brief Input management
    @author rw-r-r-0644

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <vector>
#include <functional>
#include <chrono>
#include <cstdint>
#include <pu/render.hpp>

#define BUTTON_A            (1 << 0)
#define BUTTON_B            (1 << 1)
#define BUTTON_X            (1 << 2)
#define BUTTON_Y            (1 << 3)
#define BUTTON_LSTICK       (1 << 4)
#define BUTTON_RSTICK       (1 << 5)
#define BUTTON_L            (1 << 6)
#define BUTTON_R            (1 << 7)
#define BUTTON_ZL           (1 << 8)
#define BUTTON_ZR           (1 << 9)
#define BUTTON_PLUS         (1 << 10)
#define BUTTON_MINUS        (1 << 11)
#define BUTTON_DLEFT        (1 << 12)
#define BUTTON_DUP          (1 << 13)
#define BUTTON_DRIGHT       (1 << 14)
#define BUTTON_DDOWN        (1 << 15)
#define BUTTON_LSTICK_LEFT  (1 << 16)
#define BUTTON_LSTICK_UP    (1 << 17)
#define BUTTON_LSTICK_RIGHT (1 << 18)
#define BUTTON_LSTICK_DOWN  (1 << 19)
#define BUTTON_RSTICK_LEFT  (1 << 20)
#define BUTTON_RSTICK_UP    (1 << 21)
#define BUTTON_RSTICK_RIGHT (1 << 22)
#define BUTTON_RSTICK_DOWN  (1 << 23)
#define BUTTON_TOUCH        (1 << 24)
#define BUTTON_UNKNOWN      (1 << 30)
#define BUTTON_UP           (BUTTON_DUP     | BUTTON_LSTICK_UP    | BUTTON_RSTICK_UP)
#define BUTTON_DOWN         (BUTTON_DDOWN   | BUTTON_LSTICK_DOWN  | BUTTON_RSTICK_DOWN)
#define BUTTON_LEFT         (BUTTON_DLEFT   | BUTTON_LSTICK_LEFT  | BUTTON_RSTICK_LEFT)
#define BUTTON_RIGHT        (BUTTON_DRIGHT  | BUTTON_LSTICK_RIGHT | BUTTON_RSTICK_RIGHT)

namespace pu::input
{
    class Input
    {
		public:
            void Initialize();
            void Finalize();
            bool HasInitialized();
            void ScanInput();

		private:
			static const std::array<uint32_t, 24> SDLMapping;
			uint32_t MapSDLInput(Uint8 button);
			bool initialized;
			uint32_t status;
			uint32_t prev;
	};

    uint32_t ButtonsHeld();
    uint32_t ButtonsDown();
    uint32_t ButtonsUp();
    void TouchPosition(uint32_t &x, uint32_t &y);
}
