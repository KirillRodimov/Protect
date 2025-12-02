/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *EnterButton;
    QLabel *LogLabel;
    QLineEdit *LogEdit;
    QLabel *PasLabel;
    QLineEdit *PasEdit;
    QPushButton *RegButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *adminLabel;
    QLineEdit *AdmEdit;
    QPushButton *Runbut;
    QWidget *page_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *RLogEdit;
    QLabel *label_4;
    QLineEdit *RPasEdit;
    QLabel *label_5;
    QLineEdit *RNameEdit;
    QLabel *label_6;
    QLineEdit *RPhoneEdit;
    QLabel *label_7;
    QLineEdit *RAdrEdit;
    QPushButton *RegInButton;
    QPushButton *CancelButton;
    QWidget *page_3;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *CopyButton;
    QPushButton *Edit_Button;
    QPushButton *pushButton;
    QPushButton *AddButton;
    QWidget *page_4;
    QPushButton *ConfirmButton;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QLineEdit *FNameEdit;
    QTextEdit *Soderjanie_textEdit;
    QLabel *label_2;
    QWidget *page_5;
    QLabel *Filename_label;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *Edit_textEdit;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *Save_pushButton;
    QPushButton *Cancel_pushButton;
    QWidget *page_6;
    QTextEdit *Read_textEdit;
    QLabel *Readlabel;
    QPushButton *ButtonBack;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(200, 40, 401, 371));
        page = new QWidget();
        page->setObjectName("page");
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 70, 241, 116));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        EnterButton = new QPushButton(layoutWidget);
        EnterButton->setObjectName("EnterButton");

        gridLayout->addWidget(EnterButton, 2, 0, 1, 2);

        LogLabel = new QLabel(layoutWidget);
        LogLabel->setObjectName("LogLabel");

        gridLayout->addWidget(LogLabel, 0, 0, 1, 1);

        LogEdit = new QLineEdit(layoutWidget);
        LogEdit->setObjectName("LogEdit");

        gridLayout->addWidget(LogEdit, 0, 1, 1, 1);

        PasLabel = new QLabel(layoutWidget);
        PasLabel->setObjectName("PasLabel");

        gridLayout->addWidget(PasLabel, 1, 0, 1, 1);

        PasEdit = new QLineEdit(layoutWidget);
        PasEdit->setObjectName("PasEdit");

        gridLayout->addWidget(PasEdit, 1, 1, 1, 1);

        RegButton = new QPushButton(layoutWidget);
        RegButton->setObjectName("RegButton");

        gridLayout->addWidget(RegButton, 3, 0, 1, 2);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(80, 210, 183, 58));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        adminLabel = new QLabel(layoutWidget1);
        adminLabel->setObjectName("adminLabel");

        horizontalLayout_2->addWidget(adminLabel);

        AdmEdit = new QLineEdit(layoutWidget1);
        AdmEdit->setObjectName("AdmEdit");

        horizontalLayout_2->addWidget(AdmEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        Runbut = new QPushButton(layoutWidget1);
        Runbut->setObjectName("Runbut");

        verticalLayout_3->addWidget(Runbut);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(70, 10, 172, 212));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_3);

        RLogEdit = new QLineEdit(layoutWidget2);
        RLogEdit->setObjectName("RLogEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, RLogEdit);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_4);

        RPasEdit = new QLineEdit(layoutWidget2);
        RPasEdit->setObjectName("RPasEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, RPasEdit);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_5);

        RNameEdit = new QLineEdit(layoutWidget2);
        RNameEdit->setObjectName("RNameEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, RNameEdit);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_6);

        RPhoneEdit = new QLineEdit(layoutWidget2);
        RPhoneEdit->setObjectName("RPhoneEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, RPhoneEdit);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName("label_7");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_7);

        RAdrEdit = new QLineEdit(layoutWidget2);
        RAdrEdit->setObjectName("RAdrEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, RAdrEdit);


        verticalLayout->addLayout(formLayout);

        RegInButton = new QPushButton(layoutWidget2);
        RegInButton->setObjectName("RegInButton");

        verticalLayout->addWidget(RegInButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        CancelButton = new QPushButton(layoutWidget2);
        CancelButton->setObjectName("CancelButton");

        verticalLayout_2->addWidget(CancelButton);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        layoutWidget3 = new QWidget(page_3);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(60, 10, 258, 226));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(layoutWidget3);
        listWidget->setObjectName("listWidget");

        verticalLayout_4->addWidget(listWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        CopyButton = new QPushButton(layoutWidget3);
        CopyButton->setObjectName("CopyButton");

        horizontalLayout_3->addWidget(CopyButton);

        Edit_Button = new QPushButton(layoutWidget3);
        Edit_Button->setObjectName("Edit_Button");

        horizontalLayout_3->addWidget(Edit_Button);


        verticalLayout_4->addLayout(horizontalLayout_3);

        pushButton = new QPushButton(page_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 250, 131, 24));
        AddButton = new QPushButton(page_3);
        AddButton->setObjectName("AddButton");
        AddButton->setGeometry(QRect(100, 290, 166, 24));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        ConfirmButton = new QPushButton(page_4);
        ConfirmButton->setObjectName("ConfirmButton");
        ConfirmButton->setGeometry(QRect(150, 220, 61, 24));
        layoutWidget4 = new QWidget(page_4);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(100, 60, 164, 26));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget4);
        label->setObjectName("label");

        horizontalLayout_6->addWidget(label);

        FNameEdit = new QLineEdit(layoutWidget4);
        FNameEdit->setObjectName("FNameEdit");

        horizontalLayout_6->addWidget(FNameEdit);

        Soderjanie_textEdit = new QTextEdit(page_4);
        Soderjanie_textEdit->setObjectName("Soderjanie_textEdit");
        Soderjanie_textEdit->setGeometry(QRect(100, 110, 161, 101));
        label_2 = new QLabel(page_4);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 90, 71, 16));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        Filename_label = new QLabel(page_5);
        Filename_label->setObjectName("Filename_label");
        Filename_label->setGeometry(QRect(70, 50, 191, 16));
        layoutWidget5 = new QWidget(page_5);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(70, 70, 258, 226));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        Edit_textEdit = new QTextEdit(layoutWidget5);
        Edit_textEdit->setObjectName("Edit_textEdit");

        verticalLayout_5->addWidget(Edit_textEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Save_pushButton = new QPushButton(layoutWidget5);
        Save_pushButton->setObjectName("Save_pushButton");

        horizontalLayout_4->addWidget(Save_pushButton);

        Cancel_pushButton = new QPushButton(layoutWidget5);
        Cancel_pushButton->setObjectName("Cancel_pushButton");

        horizontalLayout_4->addWidget(Cancel_pushButton);


        verticalLayout_5->addLayout(horizontalLayout_4);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        Read_textEdit = new QTextEdit(page_6);
        Read_textEdit->setObjectName("Read_textEdit");
        Read_textEdit->setGeometry(QRect(50, 60, 281, 251));
        Readlabel = new QLabel(page_6);
        Readlabel->setObjectName("Readlabel");
        Readlabel->setGeometry(QRect(50, 40, 49, 16));
        ButtonBack = new QPushButton(page_6);
        ButtonBack->setObjectName("ButtonBack");
        ButtonBack->setGeometry(QRect(150, 320, 80, 24));
        stackedWidget->addWidget(page_6);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        EnterButton->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        LogLabel->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        PasLabel->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        RegButton->setText(QCoreApplication::translate("MainWindow", "Reg", nullptr));
        adminLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\264", nullptr));
        Runbut->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Phone", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
        RegInButton->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        CancelButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        CopyButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        Edit_Button->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        AddButton->setText(QCoreApplication::translate("MainWindow", "Add file", nullptr));
        ConfirmButton->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Filename", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\264\320\265\321\200\320\266\320\260\320\275\320\270\320\265", nullptr));
        Filename_label->setText(QString());
        Save_pushButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Cancel_pushButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        Readlabel->setText(QString());
        ButtonBack->setText(QCoreApplication::translate("MainWindow", "Go back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
