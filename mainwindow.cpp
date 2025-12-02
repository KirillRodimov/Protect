#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QIntValidator>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
using namespace std;
int counter = 0;
User Guser;
int Eid_file;
QString Ename_file;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->AdmEdit->hide();
    ui->adminLabel->hide();
    ui->Runbut->hide();
    ui->AddButton->hide();

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

    ui->FNameEdit->setValidator(new QRegularExpressionValidator(re,this));

    ///
    ///
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_EnterButton_clicked()
{
    cout << "EnterButton Clicked " << endl;
    QString Tlog = ui->LogEdit->text();
    QString Tpas = generate_hash(ui->PasEdit->text().toStdString());
    if (Tlog.length() != 4)
    {
        QMessageBox::warning(this, "Ошибка ввода", "Логин должен содержать 4 цифры!");
        return;
    }
    if (ui->PasEdit->text().length() != 6 || Tpas.isEmpty())
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
    cout << "counter = " << counter << endl;
    if (rc == 1)
    {
        counter += 1;
        cout << "counter = " << counter << endl;
        if (counter == 3)
        {
            cout << "ERROR" << endl;
            QMessageBox::warning(this, "Ошибка ввода", "Вы превысили лимит попыток!"
                                                       " Введите код администратора");
            ui->AdmEdit->show();
            ui->adminLabel->show();
            ui->Runbut->show();

            ui->LogEdit->hide();
            ui->PasEdit->hide();
            ui->EnterButton->hide();
            ui->RegButton->hide();
            ui->PasLabel->hide();
            ui->LogLabel->hide();
            return;
        }
        QMessageBox::warning(this, "Ошибка ввода", "Неверные данные");
        //return;
    }
    else
    {
        QMessageBox::information(this, "Успех", "Вы успешно вошли");
        counter = 0;
        ui->stackedWidget->setCurrentIndex(2);
    }
    cout << "id = " << Euser.id << endl;


    std::list<u_file> Flist;
    Flist = get_files(db);

    ui->listWidget->clear();

    for (const u_file &u_file : Flist)
    {
        QString itemText = QString("%1: %2").arg(u_file.id_f).arg(u_file.namef);
        QListWidgetItem *item = new QListWidgetItem(itemText);

        // Сохраняем ID в данных элемента (для дальнейшего использования)
        item->setData(Qt::UserRole, u_file.id_f);
        item->setData(Qt::UserRole + 1, u_file.namef.c_str());

        ui->listWidget->addItem(item);
    }
    qDebug() << "=== СПИСОК ФАЙЛОВ ===";
    for (const u_file& u_file: Flist) {
        qDebug() << "ID:" << u_file.id_f << "Name:" << u_file.namef;
    }
    qDebug() << "=====================";
    Guser = Euser;

    return;
}


void MainWindow::on_RegInButton_clicked()
{
    QString TRlog = ui->RLogEdit->text();
    QString TRpas = generate_hash(ui->RPasEdit->text().toStdString());
    QString TRname = ui->RNameEdit->text();
    QString TRphone = ui->RPhoneEdit->text();
    QString TRadr = ui->RAdrEdit->text();

    if (TRlog.length() != 4)
    {
        QMessageBox::warning(this, "Ошибка ввода", "Логин должен содержать 4 цифры!");
        return;
    }
    if (ui->RPasEdit->text().length() != 6 || TRpas.isEmpty())
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
    cout << Ruser.pas << " -- password" << endl;
}


void MainWindow::on_Runbut_clicked()
{
    if (ui->AdmEdit->text() != "AAA")
    {
        cout << " WRONG Code " << endl;
        return;
    }
    ui->AdmEdit->hide();
    ui->adminLabel->hide();
    ui->Runbut->hide();

    ui->LogEdit->show();
    ui->PasEdit->show();
    ui->EnterButton->show();
    ui->RegButton->show();
    ui->PasLabel->show();
    ui->LogLabel->show();
    counter = 0;
    return;
}


void MainWindow::on_AddButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    return;
}


void MainWindow::on_ConfirmButton_clicked()
{
    QString TFname = ui->FNameEdit->text();
    QString all_text = ui->Soderjanie_textEdit->toPlainText();
    qDebug() << "Содержимое:" << all_text;
    set_files(db, &TFname, &all_text);
    return;
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    cout << Guser.id << " Id Guser" << endl;
    ui->CopyButton->setEnabled(false);
    ui->Edit_Button->setEnabled(false);

    int fileId = item->data(Qt::UserRole).toInt();
    QString fileName = item->data(Qt::UserRole + 1).toString();
    Eid_file = fileId;
    Ename_file = fileName;
    cout << Eid_file << " Eid " << Ename_file.toStdString() << " Ename" << endl;
    rule Rul;
    Rul = check_rules(db, Guser.id, fileId);
    cout << Rul.C << " C " << Rul.E << " E " << endl;
    if (Rul.C == 1)
    {
        ui->CopyButton->setEnabled(true);
    }
    if (Rul.E == 1)
    {
        ui->Edit_Button->setEnabled(true);
    }
    return;
}


void MainWindow::on_Edit_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->Filename_label->setText(Ename_file);


    QString folderPath = "Logs"; // Имя папки в проекте

    QDir projectDir = QDir::current(); // Получаем текущую директорию проекта
    projectDir.mkpath(folderPath); // Создаем папку, если её нет[citation:2]

    QString filePath = projectDir.absoluteFilePath(folderPath + QDir::separator() + Ename_file + ".txt");

    QFileInfo fileInfo(filePath);

    if (!fileInfo.isReadable()) {
        qDebug() << "Файл не доступен для чтения:" << filePath;
        return;
    }

    cout << filePath.toStdString() << " Filepath" << endl;
    cout << Ename_file.toStdString() << " GLOBAL" << endl;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString content = in.readAll();
        qDebug() << "Прочитано содержимое длиной:" << content.length() << "символов";
        ui->Edit_textEdit->setPlainText(content);
        file.close();
    }

    return;
}


void MainWindow::on_Save_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QString folderPath = "Logs"; // Имя папки в проекте
    //QString fileName = "output.txt"; // Имя файла

    QDir projectDir = QDir::current(); // Получаем текущую директорию проекта
    projectDir.mkpath(folderPath); // Создаем папку, если её нет[citation:2]

    QString filePath = projectDir.absoluteFilePath(folderPath + QDir::separator() + Ename_file + ".txt");
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->Edit_textEdit->toPlainText();
        file.close();
    }
}


void MainWindow::on_Cancel_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->Readlabel->setText(Ename_file);


    QString folderPath = "Logs";

    QDir projectDir = QDir::current();
    projectDir.mkpath(folderPath);

    QString filePath = projectDir.absoluteFilePath(folderPath + QDir::separator() + Ename_file + ".txt");

    //QFileInfo fileInfo(filePath);


    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString content = in.readAll();
        qDebug() << "Прочитано содержимое длиной:" << content.length() << "символов";
        ui->Read_textEdit->setPlainText(content);
        file.close();
    }
}


void MainWindow::on_ButtonBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

