#include "mainwindow.h"
#include <QSettings>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <windows.h>
#include <winreg.h>

using namespace std;
extern "C"
{
#include "sqlite3.h"
}

#include <QApplication>

//C:\Anvil\Proj_qt\Protected_prog

class User
{
public:
    int id;
    int log ;
    string pas;
    string name;
    int phone;
    string email;
    string adr;
    User()
    {
        id =0;
        log = 0;
        pas = "";
        name = "";
        phone = 0;
        email = "";
        adr = "";
    }
    User(int i, int l, string p, string n, int ph, string em, string a)
    {
        id = i;
        log = l;
        pas = p;
        name = n;
        phone = ph;
        email = em;
        adr = a;
    }
    ~User()
    {
        cout << "User " << name << " deleted" << endl;
    }
};

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
        //printf("SQL error: %s\n", err);
        cout << "SQL error: " << err <<endl;
        return rc;
    }

    //printf("data inserted\n");
    cout << "data inserted" << endl;
    return rc;
};

int callback(void *notUsed, int colCount, char **columns, char **colNames)
{
    User* p_user = static_cast<User*>(notUsed);
    p_user->name =columns[0];
    return 0;
};

 int get_user (sqlite3 *db, int id, User *p_user)
{
    char *err = 0;
    int rc = 0;
    // получаем все данные из таблицы people
    char buf[1024];
    snprintf(buf, sizeof(buf),"SELECT full_name FROM Users WHERE id = %d", id );
    char *sel = buf;
    rc = sqlite3_exec(db, sel, callback,(void*) p_user, &err);
    if (rc != SQLITE_OK )
    {
        //printf("SQL error: %s\n", err);
        cout << "SQL error: " << err <<endl;
        return rc;
    }
    return rc;
};

int read_cfg(string *bios)
{
    QSettings settings("C:/Anvil/Proj_qt/Protected_prog/secret_data.ini", QSettings::IniFormat);

    *bios = settings.value("MachineGuid/key", "00000").toString().toStdString();
    //cout << str << " READED" << endl;
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
        /* alternatively:
        std::cout.write(value, BufferSize-1); // -1 to ignore the null terminator
        std::cout << std::endl;
        */
    }
    else
    {
        cerr << "Error: " << res << std::endl;
    }
    //std::system("pause");
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //cout <<"argc " << argc << " argv:" << endl;
    //for (int i = 0; i <= argc ;i++)
    //{
    //    cout << *argv[0] << endl;
    //}
    int opa = linking_computer(&argc, argv);
    if (opa == 1)
    {
        string cfg = "";
        read_cfg(&cfg);
        string mg = "";
        read_MachineGuide(&mg);
        if (cfg != mg)
        {
            cout << "Permission denied" << endl;
            return 1;
        }
    }
    MainWindow w;
    w.show();
    sqlite3 *db;    // указатель на базу данных
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
        //printf("SQL ERROR: %s\n", err);
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }

    //printf("TABLE CREATED\n");
    cout << "TABLE CREATED" << endl;
    User first;
    first.name = "AA BB";
    //first->name = "AA BB";
    rc = set_user(db, &first);
    if (rc != SQLITE_OK)
    {
        //printf("SQL ERROR: %s\n", err);
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    rc = get_user(db, 1, &first);
    if (rc != SQLITE_OK)
    {
        //printf("SQL ERROR: %s\n", err);
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    //printf("Name id = 1 --> %s\n", first.name.c_str());
    cout << "Name id = 1 --> " << first.name.c_str();
    sqlite3_close(db);
    string val = "";
    //read_cfg(&val);

    //cout << "val after read " << val << endl;
    //val = "abcd";
    //write_cfg(&val);
    read_MachineGuide(&val);
    write_cfg(&val);
    cout << "val after read MACHINEGUIDE " << val << endl;

    //----------------
    return a.exec();
}
