#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelesswindow.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QWidget>

class MainWindow : public FramelessWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;
    QWidget* mainWidget;
};

#endif // MAINWINDOW_H
