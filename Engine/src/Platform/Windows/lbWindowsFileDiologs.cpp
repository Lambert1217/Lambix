#include "Utils/lbFileDiologs.h"
#include <Windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <commdlg.h>

namespace Lambix
{
    std::string lbFileDiologs::OpenFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(glfwGetCurrentContext());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        return {};
    }

    std::string lbFileDiologs::SaveFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(glfwGetCurrentContext());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        return {};
    }
}
