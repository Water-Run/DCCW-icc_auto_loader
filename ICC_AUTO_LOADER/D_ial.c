/*
 * D_ial.c
 * A small utility for automatically loading the monitor .icc file and setting it as a boot self-starter.
 * Author: WaterRun
 * Version: 1.0
 * Time: 2025-01-14
 * File: D_ial.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shlwapi.h>
#include <stdbool.h>

#define REGISTRY_RUN_PATH "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define ICC_FILE_NAME "D_ial.icc"
#define AUTO_START_KEY "D_ial"

bool isAdmin();
void checkIccFile();
void setAutoStart();
void loadIccFile();

int main()
{
    if (!isAdmin())
    {
        printf("<ERR>CN|请以管理员权限运行本程序 |EN|Please run this program as an administrator.\n");
        system("pause");
        return 1;
    }

    checkIccFile();

    setAutoStart();

    loadIccFile();

    printf("\t{D_ial}\n\t==Success==\n");
    Sleep(800);
    return 0;
}

bool isAdmin()
{
    bool is_admin = false;
    HANDLE token_handle = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle))
    {
        TOKEN_ELEVATION elevation;
        DWORD size;
        if (GetTokenInformation(token_handle, TokenElevation, &elevation, sizeof(elevation), &size))
        {
            is_admin = elevation.TokenIsElevated;
        }
        CloseHandle(token_handle);
    }

    return is_admin;
}

void checkIccFile()
{
    if (!PathFileExistsA(ICC_FILE_NAME))
    {
        printf("<ERR>CN|未找到 D_ial.icc 文件，请将其放置在程序目录下并重命名为 D_ial.icc |EN|The file D_ial.icc was not found in the program directory. Please place it here and rename it to D_ial.icc.\n");
        system("pause");
        exit(1);
    }
}

void setAutoStart()
{
    HKEY hkey;
    DWORD result;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, REGISTRY_RUN_PATH, 0, KEY_ALL_ACCESS, &hkey) != ERROR_SUCCESS)
    {
        printf("<ERR>CN|无法访问注册表以设置开机自启动 |EN|Failed to access the registry to set auto-start.\n");
        system("pause");
        exit(1);
    }

    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);
    DWORD path_len = strlen(exe_path) + 1;
    char existing_path[MAX_PATH];
    DWORD existing_path_len = MAX_PATH;

    if (RegQueryValueExA(hkey, AUTO_START_KEY, NULL, NULL, (LPBYTE)existing_path, &existing_path_len) == ERROR_SUCCESS)
    {
        if (strcmp(existing_path, exe_path) == 0)
        {
            RegCloseKey(hkey);
            return;
        }
    }

    result = RegSetValueExA(hkey, AUTO_START_KEY, 0, REG_SZ, (const BYTE*)exe_path, path_len);
    RegCloseKey(hkey);

    if (result != ERROR_SUCCESS)
    {
        printf("<ERR>CN|无法写入注册表以设置开机自启动 |EN|Failed to write to the registry to set auto-start.\n");
        system("pause");
        exit(1);
    }

    printf("<D_ial>(CN)已设置开机自启动 (EN)has been set to boot up.\n");
}

void loadIccFile()
{
    HDC hdc = GetDC(NULL);
    if (!hdc)
    {
        printf("<ERR>CN|无法获取设备上下文 |EN|Failed to get device context (HDC).\n");
        system("pause");
        exit(1);
    }

    char icc_path[MAX_PATH];
    if (GetFullPathNameA(ICC_FILE_NAME, MAX_PATH, icc_path, NULL) == 0)
    {
        printf("<ERR>CN|无法获取 D_ial.icc 文件的完整路径 |EN|Failed to get the full path of D_ial.icc.\n");
        ReleaseDC(NULL, hdc);
        system("pause");
        exit(1);
    }

    if (!SetICMProfileA(hdc, icc_path))
    {
        printf("<ERR>CN|无法加载 D_ial.icc 文件，请检查文件是否有效 |EN|Failed to load D_ial.icc. Please check if the file is valid.\n");
        ReleaseDC(NULL, hdc);
        system("pause");
        exit(1);
    }

    printf("<D_ial>(CN)已载入ICC文件 (EN)has been load icc file.\n");
    ReleaseDC(NULL, hdc);
}