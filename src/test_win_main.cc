#include <iostream>

#include <vulkan/vulkan.h>

#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
            INT nCmdShow) {
  AllocConsole();
  AttachConsole(GetCurrentProcessId());
  freopen("CON", "w", stdout);
  SetConsoleTitle(TEXT("Test Include"));

  std::cout << "Hello, this should should up in that new window!" << std::endl;

  MessageBox(0, "Press OK", "Message Box to Pause :)", MB_SETFOREGROUND);

  return 0;
}
