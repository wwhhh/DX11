#include "PCH.h"
#include "FileSystem.h"

using namespace Utils;

std::wstring FileSystem::sResFolder = L"/../Res/";
std::wstring FileSystem::sModelsSubFolder = L"Models/";
std::wstring FileSystem::sScriptsSubFolder = L"Scripts/";
std::wstring FileSystem::sShaderSubFolder = L"Shaders/";
std::wstring FileSystem::sTextureSubFolder = L"Textures/";

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

std::wstring FileSystem::GetProgramFolder()
{
    TCHAR exeFullPath[MAX_PATH];
    GetModuleFileName(NULL, exeFullPath, MAX_PATH);
    std::wstring str = exeFullPath;

    int pos = str.find_last_of('\\', str.length());
    return str.substr(0, pos);
}

std::wstring FileSystem::GetLogFolder()
{
    return GetProgramFolder();
}

std::wstring FileSystem::GetResFolder()
{
    return GetProgramFolder() + sResFolder;
}

std::wstring FileSystem::GetModelsFolder()
{
    return GetResFolder() + sModelsSubFolder;
}

std::wstring FileSystem::GetScriptsFolder()
{
    return GetResFolder() + sScriptsSubFolder;
}

std::wstring FileSystem::GetShaderFolder()
{
    return GetResFolder() + sShaderSubFolder;
}

std::wstring FileSystem::GetTextureFolder()
{
    return GetResFolder() + sTextureSubFolder;
}