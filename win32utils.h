#ifndef WIN32UTILS_H
#define WIN32UTILS_H

#include <Windows.h>
#include <dwmapi.h>

#include <QWindow>
#include <QOperatingSystemVersion>

namespace win32utils
{
    bool isMaximized(HWND hWnd);

    MONITORINFO getMonitorInfo(HWND hWnd, DWORD dwFlags);
    int getResizeBorderThickness(HWND hWnd);
    QWindow* findWindow(HWND hWnd);

    bool isGreaterEqualVersion(QOperatingSystemVersion version);
    bool isGreaterEqualWin8_1();

    class Taskbar
    {
    public:
        ~Taskbar();
        static bool isAutoHide();
        static int getPosition(HWND hWnd);

        static const int LEFT = 0;
        static const int TOP = 1;
        static const int RIGHT = 2;
        static const int BOTTOM = 3;
        static const int NO_POSITION = 4;

        static const int AUTO_HIDE_THICKNESS = 2;
    };


    class WindowsEffectHelper
    {
    public:
        void setBasicEffect(HWND hWnd);
    };
}
#endif // WIN32UTILS_H
