#include "gamma.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void ShowMonitorList(void) {
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(dd);
    DWORD deviceIndex = 0;
    int currentMonitorCount = 0;
    
    char message[4096] = "Available monitors:\n\n";
    char temp[512];

    while (EnumDisplayDevicesA(NULL, deviceIndex, &dd, 0)) {
        if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
            currentMonitorCount++;
            
            DISPLAY_DEVICEA monitor;
            monitor.cb = sizeof(monitor);
            const char* modelStr = "Unknown";
            
            if (EnumDisplayDevicesA(dd.DeviceName, 0, &monitor, 0)) {
                modelStr = monitor.DeviceString;
            }

            const char* status = (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) 
                ? "PRIMARY" : "Secondary";

            // Используем snprintf для защиты от переполнения буфера
            snprintf(temp, sizeof(temp), "Monitor #%d:\n  System Name: %s\n  Model: %s\n  Status: %s\n\n", 
                currentMonitorCount, dd.DeviceName, modelStr, status);
            
            strncat(message, temp, sizeof(message) - strlen(message) - 1);
        }
        deviceIndex++;
    }

    if (currentMonitorCount == 0) {
        strncat(message, "No active monitors found.\n", sizeof(message) - strlen(message) - 1);
    }

    MessageBoxA(NULL, message, "Monitor Info - gamma-toggle", MB_OK | MB_ICONINFORMATION);
}

void SetMonitorGamma(GammaMode mode, int targetMonitorNumber) {
    HMODULE hGDI32 = LoadLibraryA("gdi32.dll");
    if (!hGDI32) return;

    typedef BOOL(WINAPI* Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);
	Type_SetDeviceGammaRamp pSetDeviceGammaRamp = (Type_SetDeviceGammaRamp)(void*)GetProcAddress(hGDI32, "SetDeviceGammaRamp");
    
    if (!pSetDeviceGammaRamp) {
        FreeLibrary(hGDI32);
        return;
    }

    double gammaValue = (mode == GAMMA_ENABLE) ? GAMMA_VALUE_BRIGHT : GAMMA_VALUE_DEFAULT;
    WORD GammaArray[3][RAMP_SIZE];

    for (int i = 0; i < RAMP_SIZE; i++) {
        double normalized = (double)i / (RAMP_SIZE - 1);
        double corrected = pow(normalized, gammaValue);
        int iArrayValue = (int)(corrected * RAMP_MAX);

        // Clamp значения
        if (iArrayValue > RAMP_MAX) iArrayValue = RAMP_MAX;
        if (iArrayValue < 0) iArrayValue = 0;

        GammaArray[0][i] = GammaArray[1][i] = GammaArray[2][i] = (WORD)iArrayValue;
    }

    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(dd);
    DWORD deviceIndex = 0;
    int currentMonitorCount = 0;

    while (EnumDisplayDevicesA(NULL, deviceIndex, &dd, 0)) {
        if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
            currentMonitorCount++;
            if (currentMonitorCount == targetMonitorNumber) {
                HDC hDC = CreateDCA("DISPLAY", dd.DeviceName, NULL, NULL);
                if (hDC) {
                    pSetDeviceGammaRamp(hDC, GammaArray);
                    DeleteDC(hDC);
                }
                break;
            }
        }
        deviceIndex++;
    }
    FreeLibrary(hGDI32);
}

int IsGammaEnabled(int targetMonitorNumber) {
    HMODULE hGDI32 = LoadLibraryA("gdi32.dll");
    if (!hGDI32) return 0;

    typedef BOOL(WINAPI* Type_GetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);
	Type_GetDeviceGammaRamp pGetDeviceGammaRamp = (Type_GetDeviceGammaRamp)(void*)GetProcAddress(hGDI32, "GetDeviceGammaRamp");
    
    if (!pGetDeviceGammaRamp) {
        FreeLibrary(hGDI32);
        return 0;
    }

    WORD CurrentRamp[3][RAMP_SIZE];
    int enabled = 0;

    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(dd);
    DWORD deviceIndex = 0;
    int currentMonitorCount = 0;

    while (EnumDisplayDevicesA(NULL, deviceIndex, &dd, 0)) {
        if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
            currentMonitorCount++;
            if (currentMonitorCount == targetMonitorNumber) {
                HDC hDC = CreateDCA("DISPLAY", dd.DeviceName, NULL, NULL);
                if (hDC) {
                    if (pGetDeviceGammaRamp(hDC, CurrentRamp)) {
                        if (CurrentRamp[0][128] > GAMMA_THRESHOLD) {
                            enabled = 1;
                        }
                    }
                    DeleteDC(hDC);
                }
                break;
            }
        }
        deviceIndex++;
    }

    FreeLibrary(hGDI32);
    return enabled;
}