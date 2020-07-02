#include "app.h"

int main()
{
	WHBInitCrashHandler();
	WHBLogUdpInit();
	WHBLogPrintf("main: Hello");

    if (Initialize() == 0)
    {
		WHBLogPrintf("main: Initialized");
		
        MainApplication *mainapp = new MainApplication();

		WHBLogPrintf("main: Created Mainapp");
		
        mainapp->Show();//WithFadeIn();
        
        delete mainapp;
        Finalize();
    }
    return 0;
}
