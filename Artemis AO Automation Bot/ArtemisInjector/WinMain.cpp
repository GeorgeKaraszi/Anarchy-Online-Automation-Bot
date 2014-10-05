#include <windows.h>
#include "MyGUI.h"
using namespace System;
using namespace System::Windows::Forms;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    ArtemisInjector::MyGUI form;
    Application::Run(%form);

    return 0;
}