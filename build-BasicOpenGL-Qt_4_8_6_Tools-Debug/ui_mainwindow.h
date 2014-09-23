/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "basicopenglview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    BasicOpenGLView *oglwidget;
    QLabel *label;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QLineEdit *m11;
    QLineEdit *m12;
    QLineEdit *m13;
    QLineEdit *m21;
    QLineEdit *m22;
    QLineEdit *m23;
    QLineEdit *m31;
    QLineEdit *m32;
    QLineEdit *m33;
    QGroupBox *groupBox_3;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 665);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 193, 186);"));

        gridLayout->addWidget(oglwidget, 1, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(571, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Zapfino"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: italic 20pt \"Zapfino\";"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(175, 590));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 30, 114, 32));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 70, 114, 32));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(0, 110, 114, 32));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 150, 165, 131));
        QFont font1;
        font1.setPointSize(18);
        groupBox_2->setFont(font1);
        m11 = new QLineEdit(groupBox_2);
        m11->setObjectName(QString::fromUtf8("m11"));
        m11->setGeometry(QRect(10, 40, 40, 21));
        QFont font2;
        font2.setPointSize(12);
        m11->setFont(font2);
        m12 = new QLineEdit(groupBox_2);
        m12->setObjectName(QString::fromUtf8("m12"));
        m12->setGeometry(QRect(60, 40, 40, 21));
        m12->setFont(font2);
        m13 = new QLineEdit(groupBox_2);
        m13->setObjectName(QString::fromUtf8("m13"));
        m13->setGeometry(QRect(110, 40, 40, 21));
        m13->setFont(font2);
        m21 = new QLineEdit(groupBox_2);
        m21->setObjectName(QString::fromUtf8("m21"));
        m21->setGeometry(QRect(10, 70, 40, 21));
        m21->setFont(font2);
        m22 = new QLineEdit(groupBox_2);
        m22->setObjectName(QString::fromUtf8("m22"));
        m22->setGeometry(QRect(60, 70, 40, 21));
        m22->setFont(font2);
        m23 = new QLineEdit(groupBox_2);
        m23->setObjectName(QString::fromUtf8("m23"));
        m23->setGeometry(QRect(110, 70, 40, 21));
        m23->setFont(font2);
        m31 = new QLineEdit(groupBox_2);
        m31->setObjectName(QString::fromUtf8("m31"));
        m31->setGeometry(QRect(10, 100, 40, 21));
        m31->setFont(font2);
        m32 = new QLineEdit(groupBox_2);
        m32->setObjectName(QString::fromUtf8("m32"));
        m32->setGeometry(QRect(60, 100, 40, 21));
        m32->setFont(font2);
        m33 = new QLineEdit(groupBox_2);
        m33->setObjectName(QString::fromUtf8("m33"));
        m33->setGeometry(QRect(110, 100, 40, 21));
        m33->setFont(font2);
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(5, 370, 165, 211));
        textBrowser = new QTextBrowser(groupBox_3);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(8, 27, 151, 171));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 290, 114, 32));

        gridLayout->addWidget(groupBox, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), oglwidget, SLOT(newPoly()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), MainWindow, SLOT(pushMatrix()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Test of rubber band line from mouse input.", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "New Polygon", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "    Input Matrix", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Push Matrix", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
