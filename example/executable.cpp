#include <iostream>

#include <whereami++.h>

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#if defined(_MSC_VER)
#pragma warning(push, 3)
#endif
#include <windows.h>

#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_GLOBAL 4
#define RTLD_LOCAL 8

static void* dlopen(const char* fileName, int mode)
{
  wchar_t buffer[MAX_PATH];

  if (MultiByteToWideChar(CP_UTF8, 0, fileName, -1, buffer, sizeof(buffer) / sizeof(*buffer)))
  {
    wchar_t buffer_[MAX_PATH];

    GetFullPathNameW(buffer, sizeof(buffer_) / sizeof(*buffer_), buffer_, NULL);

    return (void*)LoadLibraryW(buffer_);
  }

  return NULL;
}

static int dlclose(void* handle)
{
  return FreeLibrary((HMODULE)handle) ? 0 : -1;
}

static const char* dlerror(void)
{
  DWORD error;

  error = GetLastError();

  if (error)
  {
    static char message[1024];

    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), message, sizeof(message), NULL);

    return message;
  }

  return "no error";
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#else

#include <dlfcn.h>

#endif

int main(int argc, char** argv)
{
  std::cout << "executable path: " << whereami::getExecutablePath() << std::endl;
  whereami::whereami_path_t executablePath = whereami::getExecutablePath();
  std::cout << "  dirname: " << executablePath.dirname() << std::endl;
  std::cout << "  basename: " << executablePath.basename() << std::endl;

  std::cout << "module path: " << whereami::getModulePath() << std::endl;
  whereami::whereami_path_t modulePath = whereami::getModulePath();
  std::cout << "  dirname: " << modulePath.dirname() << std::endl;
  std::cout << "  basename: " << modulePath.basename() << std::endl;

  for (int i = 1; i < argc; ++i)
  {
    std::string prefix = "--load-library=";
    std::string arg = std::string(argv[i]);

    if (arg.compare(0, prefix.length(), prefix) == 0)
    {
      std::string name = arg.substr(prefix.length());
      void* handle;

      std::cout << std::endl;

      handle = dlopen(name.c_str(), RTLD_NOW);
      if (!handle)
        std::cout << "failed to load library: " << dlerror() << std::endl;

      if (handle)
        dlclose(handle);
    }
  }

  return 0;
}
