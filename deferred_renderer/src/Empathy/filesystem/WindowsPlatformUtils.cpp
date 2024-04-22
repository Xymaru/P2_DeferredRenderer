#include "WindowsPlatformUtils.h"

//#include <Empathy/Application.h>
//#include <Empathy/Window.h>

#include <string>
#include <shobjidl_core.h>
#include <ShlObj.h>
#include <filesystem>
#include <Windows.h>

#include <Empathy/Debug.h>

namespace EM {
    std::string FileDialogs::OpenFile(const char* file)
    {
        OPENFILENAMEA ofn; //common dialog box structure
        CHAR szFile[MAX_PATH] = { 0 }; // if using TCHAR macros

        //Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        //ofn.hwndOwner = (HWND)Application::GetInstance()->window->GetNativeWindow();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = file;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return std::string();
    }

    std::string FileDialogs::SaveFile(const char* file)
    {
        OPENFILENAMEA ofn; //common dialog box structure
        CHAR szFile[MAX_PATH] = { 0 }; // if using TCHAR macros

        //Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        //ofn.hwndOwner = (HWND)Application::GetInstance()->window->GetNativeWindow();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = file;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return std::string();
    }

    std::string FileDialogs::SelectFolder()
    {
        LPWSTR outputDir = NULL;

        IFileDialog* pfd;
        if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
        {
            DWORD dwOptions;
            if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
            {
                pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
            }
            if (SUCCEEDED(pfd->Show(NULL)))
            {
                IShellItem* psi;
                if (SUCCEEDED(pfd->GetResult(&psi)))
                {
                    if (!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &outputDir)))
                    {
                        Debug::Log("FileDialogs", "Failed absolute parsing of dir path!");
                    }
                    psi->Release();
                }
            }
            pfd->Release();

            if (outputDir == NULL)
                return std::string();

            std::wstring wstr = outputDir;
            std::string result(wstr.begin(), wstr.end());

            return result;
        }

        return "";
    }
    std::string FileDialogs::GetDocumentsFolder()
    {
        CHAR documents[MAX_PATH];
        HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents);
        if (result == S_OK)
            return std::string(documents);
        else
            return "";
    }
    std::string FileDialogs::GetDefaultProjectPath()
    {
        std::filesystem::path path = GetDocumentsFolder();
        path /= "Empathy projects";

        if (!std::filesystem::exists(path))
            std::filesystem::create_directories(path);

        return path.string();
    }

    void FileDialogs::OpenDefaultFile(const char* path)
    {
        ShellExecuteA(0, "open", path, NULL, NULL, SW_SHOWNORMAL); 
    }
}
