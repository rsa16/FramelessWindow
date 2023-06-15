#include "titlebar.h"
#include "ui_titlebar.h"
#include <iostream>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Titlebar)
{
    ui->setupUi(this);

    restoreIcon.addFile(":/icons/restore.svg", QSize(), QIcon::Normal, QIcon::On);
    maximizeIcon.addFile(":/icons/max.svg", QSize(), QIcon::Normal, QIcon::On);

    connect(ui->maxrest, &QPushButton::clicked, this, &TitleBar::handleMinMax);
    connect(ui->min, &QPushButton::clicked, this, &TitleBar::showMinimized);
    connect(ui->close, &QPushButton::clicked, this, &TitleBar::closeWin);

    window()->installEventFilter(this);
}

void TitleBar::closeWin()
{
    std::cout << "this hsdasould work tf??" << "\n";
    window()->close();
}

void TitleBar::handleMinMax()
{
    std::cout << "this hould work tf??" << "\n";
    showMaximized();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        _move();
    }
    return QWidget::mousePressEvent(event);
}

void TitleBar::_move()
{
    windowHandle()->startSystemMove();
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }
    handleMinMax();
}

bool TitleBar::eventFilter(QObject *obj, QEvent *e)
{
    if (window() == obj)
    {
        if (e->type() == QEvent::WindowStateChange)
        {
            if (window()->isMaximized())
            {
                ui->maxrest->setToolTip("Restore");
                ui->maxrest->setIcon(QIcon(":/icons/restore.svg"));
            } else {
                ui->maxrest->setToolTip("Maximize");
                ui->maxrest->setIcon(QIcon(":/icons/max.svg"));
            }
        }

        if (e->type() == QEvent::LayoutRequest)
        {
            setMaximumHeight(sizeHint().height()); // maintain correct titlebar height
        }
    }

    return QWidget::eventFilter(obj, e);
}

TitleBar::~TitleBar()
{
    delete ui;
}



