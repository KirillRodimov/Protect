#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QIntValidator>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->RegButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->CancelButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    ui->LogEdit->setValidator(new QIntValidator(0, 9999, this));
    ui->LogEdit->setMaxLength(4);

    ui->PasEdit->setMaxLength(6);

    ui->RLogEdit->setValidator(new QIntValidator(0, 9999, this));
    ui->RLogEdit->setMaxLength(4);

    ui->RPasEdit->setMaxLength(6);

    ui->RPhoneEdit->setValidator(new QIntValidator(0, INT_MAX, this));
    QRegularExpression re("[A-Za-zА-Яа-яЁё]*");
    ui->RNameEdit->setValidator(new QRegularExpressionValidator(re,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_EnterButton_clicked()
{
    cout << "EnterButton Clicked " << endl;
    QString Tlog = ui->LogEdit->text();
    QString Tpas = ui->PasEdit->text();
    if (Tlog.length() != 4)
    {
        QMessageBox::warning(this, "Ошибка ввода", "Логин должен содержать 4 цифры!");
        return;
    }
    if (Tpas.length() != 6 || Tpas.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка ввода", "Пароль должен содержать 6 символов!");
        return;
    }
    cout << Tlog.toStdString() << " login " << Tpas.toStdString() << " Pas" << endl;
}


void MainWindow::on_RegInButton_clicked()
{
    QString TRlog = ui->RLogEdit->text();
    QString TRpas = ui->RPasEdit->text();
    QString TRname = ui->RNameEdit->text();
    QString TRphone = ui->RPhoneEdit->text();
    QString TRadr = ui->RAdrEdit->text();
    if (TRlog.length() != 4)
    {
        QMessageBox::warning(this, "Ошибка ввода", "Логин должен содержать 4 цифры!");
        return;
    }
    if (TRpas.length() != 6 || TRpas.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка ввода", "Пароль должен содержать 6 символов!");
        return;
    }
    if (TRname.isEmpty() || TRphone.isEmpty() || TRadr.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка ввода", "Заполните все поля");
        return;
    }
    cout << TRlog.toStdString() << " login " << TRpas.toStdString() << " Pas " << TRname.toStdString() << " name " << TRphone.toStdString() << " Phone " << TRadr.toStdString() << " adr " << endl;
}

