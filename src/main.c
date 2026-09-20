#include "gamma.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    int argc;
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);

    int targetMonitor = 1; 
    GammaMode mode = GAMMA_TOGGLE;          

    if (argc >= 2) {
        if (wcscmp(argvW[1], L"list") == 0 || wcscmp(argvW[1], L"0") == 0) {
            ShowMonitorList();
            LocalFree(argvW);
            return 0;
        }
        
        if (wcscmp(argvW[1], L"1") == 0) {
            mode = GAMMA_ENABLE;
        } else if (wcscmp(argvW[1], L"2") == 0) {
            mode = GAMMA_DISABLE;
        }

        if (argc >= 3) {
            targetMonitor = _wtoi(argvW[2]);
            if (targetMonitor < 1) {
                targetMonitor = 1; 
            }
        }
    }

    if (mode == GAMMA_TOGGLE) {
        if (IsGammaEnabled(targetMonitor)) {
            SetMonitorGamma(GAMMA_DISABLE, targetMonitor); 
        } else {
            SetMonitorGamma(GAMMA_ENABLE, targetMonitor); 
        }
    } else {
        SetMonitorGamma(mode, targetMonitor);
    }

    LocalFree(argvW);
    return 0;
}