#include "win32utils.h"
#include <QGuiApplication>
#include <cmath>

namespace win32utils
{
    bool isMaximized(HWND hWnd)
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);

        if (!GetWindowPlacement(hWnd, &windowPlacement)) {
            return false;
        }
        return windowPlacement.showCmd == SW_MAXIMIZE;
    }

    MONITORINFO getMonitorInfo(HWND hWnd, DWORD dwFlags)
    {
        HMONITOR mon = MonitorFromWindow(hWnd, dwFlags);

        MONITORINFO mi;
        mi.cbSize = sizeof(MONITORINFO);

        GetMonitorInfo(mon, &mi);
        return mi;
    }

    int getResizeBorderThickness(HWND hWnd)
    {
        QWindow* window = findWindow(hWnd);

        int result = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(92);
        if (result > 0)
        {
            return result;
        }

        BOOL compEnabled;
        int thickness = 4;

        DwmIsCompositionEnabled(&compEnabled);

        if (compEnabled)
        {
            thickness = 8;
        }
        return round(thickness*window->devicePixelRatio());
    }

    QWindow* findWindow(HWND hWnd)
    {
        QWindowList windows = QGuiApplication::topLevelWindows();
        for (QWindow* win : windows)
        {
            if ((HWND)win->winId() == hWnd)
            {
                return win;
            }
        }
    }

    bool isGreaterEqualVersion(QOperatingSystemVersion version)
    {
        return QOperatingSystemVersion::current() >= version;
    }

    bool isGreaterEqualWin8_1()
    {
        return isGreaterEqualVersion(QOperatingSystemVersion::Windows8_1);
    }

    bool Taskbar::isAutoHide()
    {
        APPBARDATA appbarData = {
            .cbSize = sizeof(APPBARDATA),
            .hWnd = 0,
            .uCallbackMessage = 0,
            .uEdge = 0,
            .rc = RECT{0, 0, 0, 0},
            .lParam = 0
        };

        UINT taskbarState = (UINT)SHAppBarMessage(ABM_GETSTATE, &appbarData);

        return taskbarState == ABS_AUTOHIDE;
    }

    int Taskbar::getPosition(HWND hWnd)
    {
        if (isGreaterEqualWin8_1())
        {
            MONITORINFO monitorInfo = getMonitorInfo(hWnd, MONITOR_DEFAULTTONEAREST);
            RECT monitorRect = monitorInfo.rcMonitor;
            APPBARDATA appbarData = {
                .cbSize = sizeof(APPBARDATA),
                .hWnd = 0,
                .uCallbackMessage = 0,
                .uEdge = 0,
                .rc = monitorRect,
                .lParam = 0
            };
            std::vector<int> positions = {Taskbar::LEFT, Taskbar::TOP, Taskbar::RIGHT, Taskbar::BOTTOM};
            for (int position : positions)
            {
                appbarData.uEdge = position;
                if (SHAppBarMessage(11, &appbarData))
                {
                    return position;
                }
            }
        }
        APPBARDATA appbarData = {
            .cbSize = sizeof(APPBARDATA),
            .hWnd = FindWindow(L"Shell_TrayWnd", L""),
            .uCallbackMessage = 0,
            .uEdge = 0,
            .rc = RECT{0, 0, 0, 0},
            .lParam = 0
        };

        if (appbarData.hWnd != NULL)
        {
            HMONITOR windowMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
            HMONITOR taskbarMonitor = MonitorFromWindow(appbarData.hWnd, MONITOR_DEFAULTTOPRIMARY);

            if (taskbarMonitor == windowMonitor)
            {
                SHAppBarMessage(ABM_GETTASKBARPOS, &appbarData);
                return appbarData.uEdge;
            }
        }

        return Taskbar::NO_POSITION;
    }

    void WindowsEffectHelper::setBasicEffect(HWND hWnd)
    {
        MARGINS margins = {-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        LONG dwNewLong = WS_CAPTION | WS_MAXIMIZEBOX | WS_THICKFRAME | CS_DBLCLKS | WS_MINIMIZEBOX;
        SetWindowLong(hWnd, GWL_STYLE, dwNewLong);
    }
}
