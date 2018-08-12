#pragma once

#include <string>

namespace Utils
{
    class FileSystem
    {
    public:
        FileSystem();
        ~FileSystem();

        std::wstring GetProgramFolder();

        std::wstring GetLogFolder();

        std::wstring GetResFolder();
        std::wstring GetModelsFolder();
        std::wstring GetScriptsFolder();
        std::wstring GetShaderFolder();
        std::wstring GetTextureFolder();

        bool FileExists(const std::wstring& file);
        bool FileIsNewer(const std::wstring& file1, const std::wstring& file2);

    private:
        static std::wstring sLogFolder;

        static std::wstring sResFolder;
        static std::wstring sModelsSubFolder;
        static std::wstring sScriptsSubFolder;
        static std::wstring sShaderSubFolder;
        static std::wstring sTextureSubFolder;
    };
}