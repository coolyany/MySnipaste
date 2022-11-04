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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySnipasteClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MySnipasteClass)
    {
        if (MySnipasteClass->objectName().isEmpty())
            MySnipasteClass->setObjectName(QString::fromUtf8("MySnipasteClass"));
        MySnipasteClass->resize(834, 588);
        centralWidget = new QWidget(MySnipasteClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 30, 93, 28));

        horizontalLayout->addWidget(groupBox);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        MySnipasteClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MySnipasteClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 834, 26));
        MySnipasteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MySnipasteClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MySnipasteClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MySnipasteClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MySnipasteClass->setStatusBar(statusBar);

        retranslateUi(MySnipasteClass);

        QMetaObject::connectSlotsByName(MySnipasteClass);
    } // setupUi

    void retranslateUi(QMainWindow *MySnipasteClass)
    {
        MySnipasteClass->setWindowTitle(QCoreApplication::translate("MySnipasteClass", "MySnipaste", nullptr));
        label->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MySnipasteClass", "\345\267\245\345\205\267\346\240\217", nullptr));
        pushButton->setText(QCoreApplication::translate("MySnipasteClass", "\346\210\252\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MySnipasteClass: public Ui_MySnipasteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSNIPASTE_H
