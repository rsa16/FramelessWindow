/********************************************************************************
** Form generated from reading UI file 'titlebarZhwcuw.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TITLEBARZHWCUW_H
#define TITLEBARZHWCUW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Titlebar
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *contentTopBg;
    QHBoxLayout *horizontalLayout_2;
    QFrame *leftBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *title;
    QFrame *rightBtns;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *min;
    QPushButton *maxrest;
    QPushButton *close;

    void setupUi(QWidget *Titlebar)
    {
        if (Titlebar->objectName().isEmpty())
            Titlebar->setObjectName(QString::fromUtf8("Titlebar"));
        Titlebar->resize(525, 35);
        Titlebar->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
"}"));
        horizontalLayout = new QHBoxLayout(Titlebar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        contentTopBg = new QFrame(Titlebar);
        contentTopBg->setObjectName(QString::fromUtf8("contentTopBg"));
        contentTopBg->setFrameShape(QFrame::StyledPanel);
        contentTopBg->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(contentTopBg);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        leftBox = new QFrame(contentTopBg);
        leftBox->setObjectName(QString::fromUtf8("leftBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftBox->sizePolicy().hasHeightForWidth());
        leftBox->setSizePolicy(sizePolicy);
        leftBox->setMinimumSize(QSize(0, 0));
        leftBox->setFrameShape(QFrame::StyledPanel);
        leftBox->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(leftBox);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        title = new QLabel(leftBox);
        title->setObjectName(QString::fromUtf8("title"));

        horizontalLayout_3->addWidget(title);


        horizontalLayout_2->addWidget(leftBox);

        rightBtns = new QFrame(contentTopBg);
        rightBtns->setObjectName(QString::fromUtf8("rightBtns"));
        rightBtns->setMinimumSize(QSize(100, 0));
        rightBtns->setFrameShape(QFrame::StyledPanel);
        rightBtns->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(rightBtns);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        min = new QPushButton(rightBtns);
        min->setObjectName(QString::fromUtf8("min"));
        min->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/min.svg"), QSize(), QIcon::Normal, QIcon::Off);
        min->setIcon(icon);
        min->setIconSize(QSize(16, 24));
        min->setCheckable(false);
        min->setAutoDefault(false);
        min->setFlat(false);

        horizontalLayout_4->addWidget(min);

        maxrest = new QPushButton(rightBtns);
        maxrest->setObjectName(QString::fromUtf8("maxrest"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/max.svg"), QSize(), QIcon::Normal, QIcon::Off);
        maxrest->setIcon(icon1);
        maxrest->setIconSize(QSize(16, 24));

        horizontalLayout_4->addWidget(maxrest);

        close = new QPushButton(rightBtns);
        close->setObjectName(QString::fromUtf8("close"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(close->sizePolicy().hasHeightForWidth());
        close->setSizePolicy(sizePolicy1);
        close->setMinimumSize(QSize(0, 0));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon2);
        close->setIconSize(QSize(16, 25));

        horizontalLayout_4->addWidget(close);


        horizontalLayout_2->addWidget(rightBtns);


        horizontalLayout->addWidget(contentTopBg);


        retranslateUi(Titlebar);

        min->setDefault(false);


        QMetaObject::connectSlotsByName(Titlebar);
    } // setupUi

    void retranslateUi(QWidget *Titlebar)
    {
        Titlebar->setWindowTitle(QCoreApplication::translate("Titlebar", "Form", nullptr));
        title->setText(QCoreApplication::translate("Titlebar", "Screenfolds", nullptr));
        min->setText(QString());
        maxrest->setText(QString());
        close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Titlebar: public Ui_Titlebar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TITLEBARZHWCUW_H
