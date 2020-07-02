#include <pu/input/Input.hpp>

namespace pu::input
{
	static uint32_t buttons_held, buttons_down, buttons_up;
	static uint32_t touch_x, touch_y;
	
	const std::array<uint32_t, 24> Input::SDLMapping =
    {
        BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y,
        BUTTON_LSTICK, BUTTON_RSTICK,
        BUTTON_L, BUTTON_R,
        BUTTON_ZL, BUTTON_ZR,
        BUTTON_PLUS, BUTTON_MINUS,
        BUTTON_DLEFT, BUTTON_DUP, BUTTON_DRIGHT, BUTTON_DDOWN,
        BUTTON_LSTICK_LEFT, BUTTON_LSTICK_UP, BUTTON_LSTICK_RIGHT, BUTTON_LSTICK_DOWN,
        BUTTON_RSTICK_LEFT, BUTTON_RSTICK_UP, BUTTON_RSTICK_RIGHT, BUTTON_RSTICK_DOWN,
    };
    
    void Input::Initialize()
    {
		if (this->initialized)
			return;
		
        if (!SDL_WasInit(SDL_INIT_JOYSTICK))
            SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        for (int i = 0; i < SDL_NumJoysticks(); i++)
            SDL_JoystickOpen(i);
		
		this->initialized = true;
    }
    
    void Input::Finalize()
	{
		if (!this->initialized)
			return;

		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick *j = SDL_JoystickFromInstanceID(i);
			if (j && SDL_JoystickGetAttached(j))
				SDL_JoystickClose(j);
		}
		
		this->initialized = false;
	}
	
	bool Input::HasInitialized()
	{
		return this->initialized;
	}
    
    uint32_t Input::MapSDLInput(Uint8 button)
    {
        if (button > SDLMapping.size())
            return BUTTON_UNKNOWN;
        return SDLMapping[button];
    }

    void Input::ScanInput()
    {
        SDL_Event event;
        
        prev = status;

        while (SDL_PollEvent(&event))
        {
            SDL_Joystick *j;
            switch(event.type)
            {
                case SDL_JOYBUTTONDOWN:
                    status |= MapSDLInput(event.jbutton.button);
                    break;
                case SDL_JOYBUTTONUP:
                    status &= ~MapSDLInput(event.jbutton.button);
                    break;
                case SDL_JOYDEVICEADDED:
                    j = SDL_JoystickOpen(event.jdevice.which);
                    break;
                case SDL_JOYDEVICEREMOVED:
                    j = SDL_JoystickFromInstanceID(event.jdevice.which);
                    if (j && SDL_JoystickGetAttached(j))
                        SDL_JoystickClose(j);
                    break;
				case SDL_FINGERDOWN:
					if (event.tfinger.fingerId == 0)
						status |= BUTTON_TOUCH;
					[[fallthrough]];
				case SDL_FINGERMOTION:
					if (event.tfinger.fingerId == 0)
					{
						touch_x = event.tfinger.x * 1280;
						touch_y = event.tfinger.y * 720;
					}
					break;
				case SDL_FINGERUP:
					if (event.tfinger.fingerId == 0)
						status &= ~BUTTON_TOUCH;
					break;
                default:
                    break;
            }
        }
        
        buttons_held = status;
		buttons_down = status & ~prev;
		buttons_up = ~status & prev;
    }
    
    uint32_t ButtonsHeld()
    {
		return buttons_held;
    }
    
    uint32_t ButtonsDown()
    {
		return buttons_down;
    }
    
    uint32_t ButtonsUp()
    {
		return buttons_up;
    }
    
    void TouchPosition(uint32_t &x, uint32_t &y)
	{
		x = touch_x;
		y = touch_y;
	}
}
