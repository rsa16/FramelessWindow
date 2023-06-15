#include "framelesswindow.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QWidget>

FramelessWindow::FramelessWindow(QWidget *parent) : QMainWindow(parent)
{
    titleBar = new TitleBar();

    windowEffect = new win32utils::WindowsEffectHelper();
    windowEffect->setBasicEffect((HWND)winId());

    setWindowFlags(Qt::FramelessWindowHint);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(titleBar);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QWidget* mainWidget = new QWidget();

    QTextEdit* test = new QTextEdit(mainWidget);
    layout->addWidget(test);

    mainWidget->setLayout(layout);

    connect(windowHandle(), &QWindow::screenChanged, this, &FramelessWindow::onScreenChanged);

    setCentralWidget(mainWidget);
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        _move();
    }
    return QWidget::mousePressEvent(event);
}

void FramelessWindow::_move()
{
    window()->windowHandle()->startSystemMove();
}

bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG* msg = static_cast<MSG*>(message);
    LRESULT lresult;

    auto updateCursorShape = [&]()
    {
        QPoint position = QCursor::pos();
        int x = position.x() - this->x();
        int y = position.y() - this->y();

        int w = width();
        int h = height();

        bool left = x < border_width;
        bool top = y < border_width;
        bool right = x > w - border_width;
        bool bottom = y > h - border_width;

        if (top && left)
        {
            lresult = HTTOPLEFT;
        } else if (top && right)
        {
            lresult = HTTOPRIGHT;
        } else if (bottom && left)
        {
            lresult = HTBOTTOMLEFT;
        } else if (bottom && right)
        {
            lresult = HTBOTTOMRIGHT;
        } else if (left)
        {
            lresult = HTLEFT;
        } else if (right)
        {
            lresult = HTRIGHT;
        } else if (bottom)
        {
            lresult = HTBOTTOM;
        } else if (top)
        {
            lresult = HTTOP;
        }

        *result = lresult;
        return true;
    };

    auto minMaxFull = [&]()
    {
        RECT rect;

        // min max full
        if (msg->wParam != NULL)
        {
            rect = ((LPNCCALCSIZE_PARAMS)msg->lParam)->rgrc[0];
        } else {
            rect = *(LPRECT)msg->lParam;
        }

        bool max_f = win32utils::isMaximized(msg->hwnd);

        // adjust window size
        if (max_f)
        {
            int thickness = win32utils::getResizeBorderThickness(msg->hwnd);
            rect.top += thickness;
            rect.left += thickness;
            rect.right -= thickness;
            rect.bottom -= thickness;
        }

        // for auto hide taskbar
        // WHY THE FUCK ISNT IT WORKING
        if ((max_f) && win32utils::Taskbar::isAutoHide())
        {
            int taskbarPos = win32utils::Taskbar::getPosition(msg->hwnd);
            if (taskbarPos == win32utils::Taskbar::TOP)
            {
                rect.top += win32utils::Taskbar::AUTO_HIDE_THICKNESS;
            } else if (taskbarPos == win32utils::Taskbar::BOTTOM)
            {
                rect.bottom -= win32utils::Taskbar::AUTO_HIDE_THICKNESS;
            } else if (taskbarPos == win32utils::Taskbar::LEFT)
            {
                rect.left += win32utils::Taskbar::AUTO_HIDE_THICKNESS;
            } else if (taskbarPos == win32utils::Taskbar::RIGHT)
            {
                rect.right -= win32utils::Taskbar::AUTO_HIDE_THICKNESS;
            }
        }

        if (msg->wParam != NULL)
        {
            lresult = 0;
        } else {
            lresult = WVR_REDRAW;
        }
        *result = lresult;
        return true;
    };

    if (msg->hwnd != NULL)
    {
        switch (msg->message)
        {
            case WM_NCHITTEST:
                updateCursorShape();
                break;

            case WM_NCCALCSIZE:
                minMaxFull();
                break;
        }
    }

    return false;
}

void FramelessWindow::onScreenChanged()
{
    HWND hWnd = (HWND)winId();
    SetWindowPos(hWnd, NULL, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}
