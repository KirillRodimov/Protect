#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <windows.h>
#include <winreg.h>
#include <QMessageBox>
#include <QUuid>
#include <functional>

using namespace std;
extern "C"
{
#include "sqlite3.h"
}

#include <QApplication>

std::hash<std::string> hasher;

QString generate_hash(string pas)
{
    QString hash = "";
    const string salt = "dcb54d3a6401479197094363d2738b34";
    string buf = salt + pas;
    hash = QString::number((hasher(buf)));
    return hash;
}

int set_user(sqlite3 *db, User *user)
{

    char *err = 0;
    int rc = 0;
    // добавляем строку в таблицу Users
    char buf[1024];
    snprintf(buf, sizeof(buf), "INSERT INTO Users (login, password, full_name, phone, email, adress_reg) VALUES (%d, '%s', '%s', %d, '%s', '%s');",user->log, user->pas.c_str(), user->name.c_str(), user->phone, user->email.c_str(), user->adr.c_str());
    char *ins = buf;

    rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return rc;
    }
    cout << "data inserted" << endl;
    return rc;
};

int callback(void *notUsed, int colCount, char **columns, char **colNames)
{
    User* p_user = static_cast<User*>(notUsed);
    p_user->id = atoi(columns[0]);
    return 0;
};

int callback_pas(void *notUsed, int colCount, char **columns, char **colNames)
{
    User* p_user = static_cast<User*>(notUsed);
    p_user->pas = columns[0];
    return 0;
}

int check_pass (sqlite3 *db, int login, User *p_user)
{
    char *err = 0;
    int rc = 0;
    char buf[1024];
    snprintf(buf, sizeof(buf),"SELECT id FROM Users WHERE login = %d AND password = %s", login, p_user->pas.c_str());
    char *sel = buf;
    rc = sqlite3_exec(db, sel, callback,(void*) p_user, &err);
    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return -1;
    }
    if (p_user->id == -1)
    {
        return 1;
    }
    return 0;
};


int get_login (sqlite3 *db, int login, User *p_user)
{
    char *err = 0;
    int rc = 0;
    char buf[1024];
    snprintf(buf, sizeof(buf),"SELECT id FROM Users WHERE login = %d", login );
    char *sel = buf;
    rc = sqlite3_exec(db, sel, callback,(void*) p_user, &err);
    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return -1;
    }
    if (p_user->id == -1)
    {
        return 0;
    }
    return 1;
};
//Свой файл
int read_cfg(string *bios)
{
    QSettings settings("C:/Anvil/Proj_qt/Protected_prog/secret_data.ini", QSettings::IniFormat);

    *bios = settings.value("MachineGuid/key", "00000").toString().toStdString();
    return 0;
};

int write_cfg(string *bios)
{
    QSettings settings("C:/Anvil/Proj_qt/Protected_prog/secret_data.ini", QSettings::IniFormat);
    QString str = (*bios).c_str();
    settings.setValue("MachineGuid/key", str);
    return 0;
}

void read_MachineGuide(string *bios)
{
    char value[255];
    DWORD BufferSize = sizeof(value);
    LONG res = RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", "MachineGuid", RRF_RT_REG_SZ, NULL, value, &BufferSize);
    if (res == 0)
    {
        cout << value << std::endl;
        *bios = value;
    }
    else
    {
        cerr << "Error: " << res << std::endl;
    }
    return;
}

int linking_computer(int* argc, char** argv)
{
    const char* code = "LTC";
    if((argc == NULL) || (*argc != 2) || (argv[1] == NULL))
    {
        return 1;
    }
    else
    {
        if (strcmp(argv[1], code) == 0)
        {
            cout << "COMPUTER IS LINKED" << endl;
            string mg = "";
            read_MachineGuide(&mg);
            write_cfg(&mg);
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

sqlite3 *db;  // указатель на базу данных

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int opa = linking_computer(&argc, argv);
    MainWindow w;
    if (opa == 1)
    {
        string cfg = "";
        read_cfg(&cfg);
        string mg = "";
        read_MachineGuide(&mg);
        if (cfg != mg)
        {
            cout << "Permission denied" << endl;
            QMessageBox::warning(&w, "Ошибка", "Доступ запрещен");
            return 1;
        }
    }
    w.show();
    char *err = 0; //сообщение об ошибке
    // открываем подключение к базе данных
    int rc  = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return 1;
    }

    const char *table = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, login INTEGER(4), password TEXT(6),full_name TEXT, phone INTEGER, email TEXT, adress_reg TEXT);";
    rc = sqlite3_exec(db, table, 0, 0, &err);

    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    cout << "TABLE CREATED" << endl;
    QString abcd = "First";
    QString out = generate_hash(abcd.toStdString());
    cout << out.toStdString() << " -- out" << endl;
    return a.exec();
}
