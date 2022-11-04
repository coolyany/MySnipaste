/********************************************************************************
** Form generated from reading UI file 'MySnipaste.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSNIPASTE_H
#define UI_MYSNIPASTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySnipasteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MySnipasteClass)
    {
        if (MySnipasteClass->objectName().isEmpty())
            MySnipasteClass->setObjectName(QString::fromUtf8("MySnipasteClass"));
        MySnipasteClass->resize(600, 400);
        menuBar = new QMenuBar(MySnipasteClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MySnipasteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MySnipasteClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MySnipasteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MySnipasteClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MySnipasteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MySnipasteClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MySnipasteClass->setStatusBar(statusBar);

        retranslateUi(MySnipasteClass);

        QMetaObject::connectSlotsByName(MySnipasteClass);
    } // setupUi

    void retranslateUi(QMainWindow *MySnipasteClass)
    {
        MySnipasteClass->setWindowTitle(QCoreApplication::translate("MySnipasteClass", "MySnipaste", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MySnipasteClass: public Ui_MySnipasteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSNIPASTE_H
