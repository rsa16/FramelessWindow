# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'titlebarETrnXL.ui'
##
## Created by: Qt User Interface Compiler version 6.2.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import QCoreApplication, QMetaObject, QSize, QOperatingSystemVersion
from PySide6.QtGui import QIcon, Qt, QMouseEvent, QCursor, QGuiApplication
from PySide6.QtWidgets import QApplication, QFrame, QHBoxLayout, QMainWindow, QLabel, QVBoxLayout, QPushButton, QSizePolicy, QWidget, QTextEdit
from ctypes.wintypes import LPRECT, MSG, DWORD, HWND, LPARAM, RECT, UINT, BOOL
from ctypes import Structure, byref, sizeof, windll, cast, POINTER, c_int, c_bool
from win32comext.shell import shellcon
from enum import Enum
import ctypes

import rsrcs_rc
import win32con
import win32gui
import win32api
import sys

class MARGINS(Structure):
    _fields_ = [
        ("cxLeftWidth",     c_int),
        ("cxRightWidth",    c_int),
        ("cyTopHeight",     c_int),
        ("cyBottomHeight",  c_int),
    ]
    
class PWINDOWPOS(Structure):
    _fields_ = [
        ('hWnd',            HWND),
        ('hwndInsertAfter', HWND),
        ('x',               c_int),
        ('y',               c_int),
        ('cx',              c_int),
        ('cy',              c_int),
        ('flags',           UINT)
    ]

class NCCALCSIZE_PARAMS(Structure):
    _fields_ = [
        ('rgrc', RECT*3),
        ('lppos', POINTER(PWINDOWPOS))
    ]

LPNCCALCSIZE_PARAMS = POINTER(NCCALCSIZE_PARAMS)

class WindowsEffectHelper:

    def __init__(self):
        # C Libraries which are really necessary to apply Windows OS effect to Qt frameless window
        user32 = windll.LoadLibrary("user32")
        dwmapi = windll.LoadLibrary("dwmapi")
    
        self.__dwmExtendFrameIntoClientArea = dwmapi.DwmExtendFrameIntoClientArea

    # set fancy effect
    def setBasicEffect(self, hWnd):
        hWnd = int(hWnd)
        margins = MARGINS(-1, -1, -1, -1)
        self.__dwmExtendFrameIntoClientArea(hWnd, byref(margins))
        # common window value (including minimize, maximize, close, resize, animation..)
        dwNewLong = win32con.WS_CAPTION
        dwNewLong |= win32con.WS_MINIMIZEBOX
        dwNewLong |= win32con.CS_DBLCLKS | win32con.WS_THICKFRAME | win32con.WS_MAXIMIZEBOX

        win32gui.SetWindowLong(
            hWnd,
            win32con.GWL_STYLE,
            dwNewLong
        )

def isMaximized(hWnd):
    windowPlacement = win32gui.GetWindowPlacement(hWnd)
    if not windowPlacement:
        return False

    return windowPlacement[1] == win32con.SW_MAXIMIZE

def findWindow(hWnd):
    if not hWnd:
        return

    windows = QGuiApplication.topLevelWindows()
    if not windows:
        return

    for window in windows:
        if window and int(window.winId()) == hWnd:
            return window
        
def getResizeBorderThickness(hWnd):
    window = findWindow(hWnd)
    if not window:
        return 0

    result = win32api.GetSystemMetrics(win32con.SM_CXSIZEFRAME) + win32api.GetSystemMetrics(92)

    if result > 0:
        return result

    b = c_bool()
    ctypes.windll.dwmapi.DwmIsCompositionEnabled(byref(b))

    thickness = 8 if b.value else 4
    return round(thickness*window.devicePixelRatio())

def getMonitorInfo(hWnd, dwFlags):
    monitor = win32api.MonitorFromWindow(hWnd, dwFlags)
    if not monitor:
        return

    return win32api.GetMonitorInfo(monitor)

def isGreaterEqualVersion(version):
    return QOperatingSystemVersion.current() >= version

def isGreaterEqualWin8_1():
    return isGreaterEqualVersion(QOperatingSystemVersion.Windows8_1)

class APPBARDATA(Structure):
    _fields_ = [
        ('cbSize',            DWORD),
        ('hWnd',              HWND),
        ('uCallbackMessage',  UINT),
        ('uEdge',             UINT),
        ('rc',                RECT),
        ('lParam',            LPARAM),
    ]

class Taskbar:
    LEFT = 0
    TOP = 1
    RIGHT = 2
    BOTTOM = 3
    NO_POSITION = 4

    AUTO_HIDE_THICKNESS = 2

    @staticmethod
    def isAutoHide():
        appbarData = APPBARDATA(sizeof(APPBARDATA), 0,
                                0, 0, RECT(0, 0, 0, 0), 0)
        taskbarState = windll.shell32.SHAppBarMessage(
            shellcon.ABM_GETSTATE, byref(appbarData))

        return taskbarState == shellcon.ABS_AUTOHIDE

    @classmethod
    def getPosition(cls, hWnd):
        if isGreaterEqualWin8_1():
            monitorInfo = getMonitorInfo(
                hWnd, win32con.MONITOR_DEFAULTTONEAREST)
            if not monitorInfo:
                return cls.NO_POSITION

            monitor = RECT(*monitorInfo['Monitor'])
            appbarData = APPBARDATA(sizeof(APPBARDATA), 0, 0, 0, monitor, 0)
            positions = [cls.LEFT, cls.TOP, cls.RIGHT, cls.BOTTOM]
            for position in positions:
                appbarData.uEdge = position
                if windll.shell32.SHAppBarMessage(11, byref(appbarData)):
                    return position

            return cls.NO_POSITION

        appbarData = APPBARDATA(sizeof(APPBARDATA), win32gui.FindWindow(
            "Shell_TrayWnd", None), 0, 0, RECT(0, 0, 0, 0), 0)
        if appbarData.hWnd:
            windowMonitor = win32api.MonitorFromWindow(
                hWnd, win32con.MONITOR_DEFAULTTONEAREST)
            if not windowMonitor:
                return cls.NO_POSITION

            taskbarMonitor = win32api.MonitorFromWindow(
                appbarData.hWnd, win32con.MONITOR_DEFAULTTOPRIMARY)
            if not taskbarMonitor:
                return cls.NO_POSITION

            if taskbarMonitor == windowMonitor:
                windll.shell32.SHAppBarMessage(
                    shellcon.ABM_GETTASKBARPOS, byref(appbarData))
                return appbarData.uEdge

        return cls.NO_POSITION


class Ui_Titlebar(object):
    def setupUi(self, Titlebar):
        if not Titlebar.objectName():
            Titlebar.setObjectName(u"Titlebar")
        Titlebar.resize(525, 35)
        Titlebar.setStyleSheet(u"QWidget {\n"
"	background-color: #031834;\n"
"}\n"
"\n"
"#leftBox QLabel { \n"
"	font-size: 12px;\n"
"	font-weight: bold;\n"
"	color: rgb(143, 156, 179);\n"
"	padding-left: 10px;\n"
"	padding-top: 5px;\n"
"}\n"
"\n"
"#rightBtns QPushButton {\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"	border: none;\n"
"}\n"
"\n"
"#rightBtns QPushButton::hover { \n"
"	background-color: #052652;\n"
"}\n"
"\n"
"#rightBtns QPushButton::pressed {\n"
"	background-color: #09499e;\n"
"}")
        self.horizontalLayout = QHBoxLayout(Titlebar)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.contentTopBg = QFrame(Titlebar)
        self.contentTopBg.setObjectName(u"contentTopBg")
        self.contentTopBg.setFrameShape(QFrame.StyledPanel)
        self.contentTopBg.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.contentTopBg)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.leftBox = QFrame(self.contentTopBg)
        self.leftBox.setObjectName(u"leftBox")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.leftBox.sizePolicy().hasHeightForWidth())
        self.leftBox.setSizePolicy(sizePolicy)
        self.leftBox.setMinimumSize(QSize(0, 0))
        self.leftBox.setFrameShape(QFrame.StyledPanel)
        self.leftBox.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_3 = QHBoxLayout(self.leftBox)
        self.horizontalLayout_3.setSpacing(0)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.title = QLabel(self.leftBox)
        self.title.setObjectName(u"title")

        self.horizontalLayout_3.addWidget(self.title)

        self.horizontalLayout_2.addWidget(self.leftBox)

        self.rightBtns = QFrame(self.contentTopBg)
        self.rightBtns.setObjectName(u"rightBtns")
        self.rightBtns.setMinimumSize(QSize(100, 0))
        self.rightBtns.setFrameShape(QFrame.StyledPanel)
        self.rightBtns.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_4 = QHBoxLayout(self.rightBtns)
        self.horizontalLayout_4.setSpacing(0)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.min = QPushButton(self.rightBtns)
        self.min.setObjectName(u"min")
        self.min.setStyleSheet(u"")
        icon = QIcon()
        icon.addFile(u":/icons/min.svg", QSize(), QIcon.Normal, QIcon.Off)
        self.min.setIcon(icon)
        self.min.setIconSize(QSize(16, 24))
        self.min.setCheckable(False)
        self.min.setAutoDefault(False)
        self.min.setFlat(False)

        self.horizontalLayout_4.addWidget(self.min)

        self.maxrest = QPushButton(self.rightBtns)
        self.maxrest.setObjectName(u"maxrest")
        icon1 = QIcon()
        icon1.addFile(u":/icons/max.svg", QSize(), QIcon.Normal, QIcon.Off)
        self.maxrest.setIcon(icon1)
        self.maxrest.setIconSize(QSize(16, 24))

        self.horizontalLayout_4.addWidget(self.maxrest)

        self.close = QPushButton(self.rightBtns)
        self.close.setObjectName(u"close")
        sizePolicy1 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.close.sizePolicy().hasHeightForWidth())
        self.close.setSizePolicy(sizePolicy1)
        self.close.setMinimumSize(QSize(0, 0))
        icon2 = QIcon()
        icon2.addFile(u":/icons/close.svg", QSize(), QIcon.Normal, QIcon.Off)
        self.close.setIcon(icon2)
        self.close.setIconSize(QSize(16, 25))

        self.horizontalLayout_4.addWidget(self.close)


        self.horizontalLayout_2.addWidget(self.rightBtns)


        self.horizontalLayout.addWidget(self.contentTopBg)


        self.retranslateUi(Titlebar)

        self.min.setDefault(False)


        QMetaObject.connectSlotsByName(Titlebar)
    # setupUi

    def retranslateUi(self, Titlebar):
        Titlebar.setWindowTitle(QCoreApplication.translate("Titlebar", u"Form", None))
        self.title.setText(QCoreApplication.translate("Titlebar", u"Screenfolds", None))
        self.min.setText("")
        self.maxrest.setText("")
        self.close.setText("")
    # retranslateUi

class TitleBar(QWidget):
    def __init__(self, base_widget=None):
        super().__init__(base_widget)

        self.ui = Ui_Titlebar()
        self.ui.setupUi(self)

        self.restoreIcon = QIcon()
        self.restoreIcon.addFile(u":/icons/restore.svg", QSize(), QIcon.Normal, QIcon.Off)

        self.maximizeIcon = QIcon()
        self.maximizeIcon.addFile(u":/icons/max.svg", QSize(), QIcon.Normal, QIcon.Off)

        self.ui.maxrest.clicked.connect(self.maximize)
        self.ui.min.clicked.connect(self.window().showMinimized)
        self.ui.close.clicked.connect(self.window().close)

        self.window().installEventFilter(self)

    def maximize(self):
        if self.window().isMaximized():
            self.window().showNormal()
        else:
            self.window().showMaximized()

    def mouseDoubleClickEvent(self, event: QMouseEvent) -> None:
        if event.button() != Qt.LeftButton:
            return
        self.maximize()
    
    def mousePressEvent(self, event: QMouseEvent) -> None:
        if event.button() == Qt.LeftButton:
            self._move()
        return super().mousePressEvent(event)
    
    def _move(self):
        window = self.window().windowHandle()
        window.startSystemMove()

    def eventFilter(self, obj, e):
        if obj is self.window():
            if e.type() == 105:
                if self.window().isMaximized():
                    self.ui.maxrest.setIcon(self.restoreIcon)
                else:
                    self.ui.maxrest.setIcon(self.maximizeIcon)

            if e.type() == 76:
                self.setMaximumHeight(self.sizeHint().height())
    
class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        self.borderWidth = 5
        self.titlebar = TitleBar(self)

        newFlags = self.windowFlags() | Qt.FramelessWindowHint
        self.setWindowFlags(newFlags)

        self._windowEffect = WindowsEffectHelper()
        self._windowEffect.setBasicEffect(self.winId())

        self.windowHandle().screenChanged.connect(self.onScreenChanged)

    def mousePressEvent(self, event: QMouseEvent) -> None:
        if event.button() == Qt.LeftButton:
            self._move()
        return super().mousePressEvent(event)
    
    def _move(self):
        window = self.window().windowHandle()
        window.startSystemMove()

    def nativeEvent(self, e, message):
        msg = MSG.from_address(message.__int__())
        if msg.hWnd:
            if msg.message == win32con.WM_NCHITTEST:
                pos = QCursor.pos()
                x = pos.x() - self.x()
                y = pos.y() - self.y()

                w, h = self.width(), self.height()

                left = x < self.borderWidth
                top = y < self.borderWidth
                right = x > w - self.borderWidth
                bottom = y > h - self.borderWidth

                if top and left:
                    return True, win32con.HTTOPLEFT
                elif top and right:
                    return True, win32con.HTTOPRIGHT
                elif bottom and left:
                    return True, win32con.HTBOTTOMLEFT
                elif bottom and right:
                    return True, win32con.HTBOTTOMRIGHT
                elif left:
                    return True, win32con.HTLEFT
                elif top:
                    return True, win32con.HTTOP
                elif right:
                    return True, win32con.HTRIGHT
                elif bottom:
                    return True, win32con.HTBOTTOM

            elif msg.message == win32con.WM_NCCALCSIZE:
                if msg.wParam:
                    rect = cast(msg.lParam, LPNCCALCSIZE_PARAMS).contents.rgrc[0]
                else:
                    rect = cast(msg.lParam, LPRECT).contents
                
                max_f = isMaximized(msg.hWnd)

                if max_f:
                    thickness = getResizeBorderThickness(msg.hWnd)
                    rect.top += thickness
                    rect.left += thickness
                    rect.right -= thickness
                    rect.bottom -= thickness
                
                if isMaximized and Taskbar.isAutoHide():
                    position = Taskbar.getPosition(msg.hWnd)
                    if position == Taskbar.LEFT:
                        rect.top += Taskbar.AUTO_HIDE_THICKNESS
                    elif position == Taskbar.BOTTOM:
                        rect.bottom -= Taskbar.AUTO_HIDE_THICKNESS
                    elif position == Taskbar.LEFT:
                        rect.left += Taskbar.AUTO_HIDE_THICKNESS
                    elif position == Taskbar.RIGHT:
                        rect.right += Taskbar.AUTO_HIDE_THICKNESS
                
                result = 0 if not msg.wParam else win32con.WVR_REDRAW
                return True, result
        return super().nativeEvent(e, message)

    def onScreenChanged(self):
        hWnd = int(self.windowHandle().winId())
        win32gui.SetWindowPos(hWnd, None, 0, 0, 0, 0, win32con.SWP_NOMOVE | win32con.SWP_NOSIZE | win32con.SWP_FRAMECHANGED)
    
class MyMainWindow(MainWindow):
    def __init__(self):
        super().__init__()
        
        lay = QVBoxLayout()
        lay.addWidget(self.titlebar)
        lay.setContentsMargins(0, 0, 0, 0)
        lay.setSpacing(0)
        
        mainWidget = QWidget()
        lay.addWidget(QTextEdit())
        mainWidget.setLayout(lay)

        self.setCentralWidget(mainWidget)

if __name__ == "__main__":
    app = QApplication()
    main = MyMainWindow()
    main.show()
    sys.exit(app.exec())
    