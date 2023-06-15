#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QIcon>
#include <QMouseEvent>
#include <QWindow>

namespace Ui {
class Titlebar;
}

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    void _move();
    bool eventFilter(QObject *object, QEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void handleMinMax();
    void closeWin();

private:
    Ui::Titlebar *ui;

    QIcon restoreIcon;
    QIcon maximizeIcon;
};

#endif // TITLEBAR_H
