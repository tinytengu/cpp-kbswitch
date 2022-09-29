#include <stdio.h>
#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "user32")

#define LANG_EN 0x409
#define LANG_KR 0x412

unsigned int getInputMethod(HWND hwnd) {
    DWORD threadId = GetWindowThreadProcessId(hwnd, NULL);
    HKL currentLayout = GetKeyboardLayout(threadId);
    return (unsigned int)currentLayout & 0x0000FFFF;
}

void switchLayout(HWND hwnd, DWORD layout) {
    PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)layout);
    PostMessage(hwnd, WM_INPUTLANGCHANGE, 0, (LPARAM)layout);
}

unsigned int getProcessId(HWND handle) {
    unsigned long processId = 0;
    GetWindowThreadProcessId(handle, &processId);
    return processId;
}

void getProcessName(unsigned int processId, TCHAR buffer[MAX_PATH]) {
    HANDLE processHandle = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        processId
    );

    GetModuleFileNameEx(processHandle, 0, buffer, MAX_PATH);
    CloseHandle(processHandle);
}

int main() {
    HWND consoleHandle = GetConsoleWindow();
    ShowWindow(consoleHandle, SW_HIDE);

    while(true) {
        HWND foregroundHandle = GetForegroundWindow();
        if(foregroundHandle == consoleHandle) {
            continue;
        }

        unsigned long processId = getProcessId(foregroundHandle);
        TCHAR processName[MAX_PATH];
        getProcessName(processId, processName);

        if(getInputMethod(foregroundHandle) == LANG_EN) {
            switchLayout(foregroundHandle, LANG_KR);
        }
    }
    return 0;
}