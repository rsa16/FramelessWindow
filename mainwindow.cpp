#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : FramelessWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    layout = new QVBoxLayout();
    layout->addWidget(titleBar);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    mainWidget = new QWidget();

    QTextEdit* test = new QTextEdit(mainWidget);
    layout->addWidget(test);

    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);
}
