#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

class WindowSelector {
private:
    HWND targetWindow;
    int targetX;
    int targetY;
    std::string targetTitle;

public:
    WindowSelector() : targetWindow(NULL), targetX(-1), targetY(-1) {}

    HWND findWindowByPosition(int x, int y) {
        targetX = x;
        targetY = y;
        targetTitle.clear();
        EnumWindows(WindowSelector::enumWindowsProc, reinterpret_cast<LPARAM>(this));
        return targetWindow;
    }

    HWND findWindowByTitle(const std::string& title) {
        targetTitle = title;
        targetX = targetY = -1;
        EnumWindows(WindowSelector::enumWindowsProc, reinterpret_cast<LPARAM>(this));
        return targetWindow;
    }

    void bringWindowToFront() {
        if (targetWindow) {
            SetForegroundWindow(targetWindow);
        }
    }

    RECT getWindowSize() {
        RECT rect = { 0, 0, 0, 0 };
        if (targetWindow) {
            GetWindowRect(targetWindow, &rect);
        }
        return rect;
    }

private:
    static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam) {
        WindowSelector* self = reinterpret_cast<WindowSelector*>(lParam);
        return self->checkWindow(hwnd);
    }

    BOOL checkWindow(HWND hwnd) {
        if (!targetTitle.empty()) {
            char windowTitle[256];
            GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
            if (targetTitle == windowTitle) {
                targetWindow = hwnd;
                return FALSE; // Stop enumeration
            }
        }
        else if (targetX != -1 && targetY != -1) {
            RECT rect;
            if (GetWindowRect(hwnd, &rect)) {
                if (targetX >= rect.left && targetX < rect.right &&
                    targetY >= rect.top && targetY < rect.bottom) {
                    targetWindow = hwnd;
                    return FALSE; // Stop enumeration
                }
            }
        }
        return TRUE; // Continue enumeration
    }
};