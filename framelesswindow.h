#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "titlebar.h"
#include "win32utils.h"

class FramelessWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FramelessWindow(QWidget *parent = nullptr);
    TitleBar* titleBar;

    void mousePressEvent(QMouseEvent *event) override;
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;

private slots:
    void onScreenChanged();

private:
    int border_width = 5;
    win32utils::WindowsEffectHelper* windowEffect;
    void _move();

};

#endif // FRAMELESSWINDOW_H
