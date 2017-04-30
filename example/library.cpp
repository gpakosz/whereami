#include <iostream>

#include <whereami++.h>

#if defined(__GNUC__) && !defined(_WIN32)
__attribute__((constructor))
#endif
static void load()
{
  std::cout << "library loaded" << std::endl;

  std::cout << "executable path: " << whereami::getExecutablePath() << std::endl;
  whereami::whereami_path_t executablePath = whereami::getExecutablePath();
  std::cout << "  dirname: " << executablePath.dirname() << std::endl;
  std::cout << "  basename: " << executablePath.basename() << std::endl;

  std::cout << "module path: " << whereami::getModulePath() << std::endl;
  whereami::whereami_path_t modulePath = whereami::getModulePath();
  std::cout << "  dirname: " << modulePath.dirname() << std::endl;
  std::cout << "  basename: " << modulePath.basename() << std::endl;
}

#if defined(__GNUC__) && !defined(_WIN32)
__attribute__((destructor))
#endif
static void unload()
{
  std::cout << "library unloaded" << std::endl;
}

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#if defined(_MSC_VER)
#pragma warning(push, 3)
#endif
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
      load();
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      unload();
      break;
  }
  return TRUE;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif
