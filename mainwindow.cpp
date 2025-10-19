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
    User Euser;
    string password = "";
    int rc = 0;
    cout << "rc = " << rc << endl;
    Euser.id = -1;
    Euser.log = Tlog.toInt();
    Euser.pas = Tpas.toStdString();
    password = Euser.pas;
    rc = check_pass(db, Euser.log, &Euser);
    cout << "rc = " << rc << " password "<< password << " Euser.pas " << Euser.pas << endl;
    if (rc == 1)
    {
        QMessageBox::warning(this, "Ошибка ввода", "Неверные данные");
        return;
    }
    else
    {
        QMessageBox::information(this, "Успех", "Вы успешно вошли");
        ui->stackedWidget->setCurrentIndex(2);
    }
    cout << "id = " << Euser.id << endl;
    return;
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
    User Ruser;
    int rc = 0;
    cout << "rc = " << rc << endl;
    Ruser.id = -1;
    Ruser.log = TRlog.toInt();
    Ruser.pas = TRpas.toStdString();
    Ruser.name = TRname.toStdString();
    Ruser.phone = TRphone.toInt();
    Ruser.adr = TRadr.toStdString();
    rc = get_login(db, Ruser.log, &Ruser);
    cout << "id = " << Ruser.id << endl;
    if (rc == 0)
    {
        set_user(db, &Ruser);
        cout << "User putted in base" << endl;
        QMessageBox::information(this, "Успех", "Вы успешно зарегестрировались");
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка ввода", "Пользователь с таким логином уже существует!");
        return;
    }
    cout << "id = " << Ruser.id << endl;
}

