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
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QByteArray>

using namespace std;
extern "C"
{
#include "sqlite3.h"
}

#include <QApplication>

std::hash<std::string> hasher;
//std::list<u_file> Lfiles;

int callback_key(void *notUsed, int colCount, char **columns, char **colNames)
{
    //std::list<u_file>* Lis = static_cast<list<u_file>*> (notUsed);
    string* check_key = static_cast<string*> (notUsed);
    *check_key = columns[0];
    cout << *check_key << " KEY FROM DB" << endl;
    return 0;
}

string take_modif(string* filename, sqlite3 *db)
{
    char *err = 0;
    int rc = 0;
    string dbkey;
    char buf[1024];
    snprintf(buf, sizeof(buf),"SELECT Last_modif FROM Files WHERE File_name = '%s'", filename->c_str());

    rc = sqlite3_exec(db, buf, callback_key,(void*) &dbkey, &err);
    //cout << "Hi " << rc <<endl;
    if (rc != SQLITE_OK )
    {
        cout << "SQL error: takemodif" << err <<endl;
        return dbkey;
    }
    return dbkey;
}

int insert_key(string* key, sqlite3 *db, string* filename)
{
    char *err = 0;
    int rc = 0;
    char buf[1024];
    cout << " SAVEDB " << *key << " HASH " << *key << " FN" <<endl;
    snprintf(buf, sizeof(buf), "UPDATE Files SET Last_modif = '%s' WHERE File_name = '%s'", key->c_str(), filename->c_str());
    //cout << " SAVEDB1 " << endl;
    char *ins = buf;

    rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: UPDATE FILE MODIF" << err <<endl;
        return rc;
    }
    return 0;
}

bool createTimestampedCopyFile(const QString& originalFileName)
{
    QString originalPath = "Logs/" + originalFileName + ".txt";
    QFile originalFile(originalPath);


    if (!originalFile.exists()) {
        return false;
    }

    QFileInfo fileInfo(originalFileName + ".txt");
    QString baseName = fileInfo.completeBaseName();
    QString suffix = fileInfo.suffix();

    cout << suffix.toStdString() << " SUFFIX" << endl;

    //QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString backupFileName;

    if (suffix.isEmpty())
    {
        backupFileName = baseName + "_copy";
    }
    else
    {
        backupFileName = baseName + "_copy" + ".secretextension";
    }

    QString backupPath = "Logs/" + backupFileName;
    QFile backupFile(backupPath);

    if (backupFile.exists())
    {
        if (!backupFile.remove())
        {
            qDebug() << "Ошибка: не удалось удалить старую копию" << backupPath;
            qDebug() << "Причина:" << backupFile.errorString();
            return false;
        }
        qDebug() << "Старая копия удалена:" << backupPath;
    }

    if (originalFile.copy(backupPath))
    {
        qDebug() << "Резервная копия создана:";
        qDebug() << "  Оригинал: " << originalPath;
        qDebug() << "  Копия:    " << backupPath;
        qDebug() << "  Размер:   " << originalFile.size() << "байт";
        return true;
    }
    else
    {
        qDebug() << "Ошибка создания копии";
        qDebug() << "Причина:" << originalFile.errorString();
        return false;
    }

}


int callback_hashfile(void *notUsed, int colCount, char **columns, char **colNames)
{
    //std::list<u_file>* Lis = static_cast<list<u_file>*> (notUsed);
    string* hash = static_cast<string*> (notUsed);
    *hash = columns[0];
    cout << *hash << " CHECK DB HASH " << endl;
    return 0;
};

string check_hash(string* truehash, string* filename, sqlite3 *db)
{
    string a = "AAAAAAAAA";

    char *err = 0;
    int rc = 0;
    string nottruehash;
    char buf[1024];
    //snprintf(buf, sizeof(buf),"SELECT * FROM Files WHERE File_name = '%s' AND File_hash = '%s'", filename->c_str(), truehash->c_str());
    snprintf(buf, sizeof(buf),"SELECT File_hash FROM Files WHERE File_name = '%s'", filename->c_str());

    rc = sqlite3_exec(db, buf, callback_hashfile,(void*) &nottruehash, &err);
    //cout << "Hi " << rc <<endl;
    if (rc != SQLITE_OK )
    {
        cout << "SQL error: get files" << err <<endl;
        return nottruehash;
    }
    return nottruehash;
}

string generate_file_hash(string* content, string* filename ,string* path)
{
    string fullname = *content + *filename + *path;
    cout << fullname << " FULL NAME" << endl;
    QString file_hash = "";
    file_hash = QString::number((hasher(fullname)));
    cout << file_hash.toStdString() << " FILEHASH" << endl;
    return file_hash.toStdString();
}

int savehash_to_db(string* filename, sqlite3 *db, string* hash)
{
    char *err = 0;
    int rc = 0;
    char buf[1024];
    cout << " SAVEDB " << *hash << " HASH " << *filename << " FN" <<endl;
    snprintf(buf, sizeof(buf), "UPDATE Files SET File_hash = '%s' WHERE File_name = '%s'", hash->c_str(), filename->c_str());
    cout << " SAVEDB1 " << endl;
    char *ins = buf;

    rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: UPDATE FILE HASH" << err <<endl;
        return rc;
    }
    return 0;
}
int callback_rule(void *notUsed, int colCount, char **columns, char **colNames)
{
    rule* pravila = static_cast<rule*> (notUsed);
    pravila->C = atoi(columns[0]);
    pravila->E = atoi(columns[1]);
    cout << pravila->C << " C " << pravila->E << " E " << endl;
    return 0;
};

rule check_rules(sqlite3 *db, int id_u, int id_f)
{
    rule ruleuser;
    char *err = 0;
    int rc = 0;
    char buf[1024];
    snprintf(buf, sizeof(buf), "SELECT C, E FROM Rules WHERE id_u = %d AND id_f = %d", id_u, id_f);
    char *sel = buf;
    rc = sqlite3_exec(db, sel, callback_rule,(void*) &ruleuser, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: check rules" << err <<endl;
        return ruleuser;
    }
    return ruleuser;
}

int callback_file(void *notUsed, int colCount, char **columns, char **colNames)
{
    std::list<u_file>* Lis = static_cast<list<u_file>*> (notUsed);
    u_file f;
    f.id_f = atoi(columns[0]);
    f.namef = columns[1];
    cout << f.namef << " name " << f.id_f << " id " << endl;
    Lis->push_back(f);
    return 0;
};
/*
int create_file(sqlite3 *db, int id_u, int id_f)
{
    char *err = 0;
    int rc = 0;
    // добавляем строку в таблицу Files
    char buf[1024];
    snprintf(buf, sizeof(buf), "INSERT INTO Rules (id_u, id_f, C, E) VALUES ('%d, %d, %d, %d,')", id_u, id_f, 1, 1);
    char *ins = buf;

    rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return rc;
    }
}
*/

int insert_rules(sqlite3 *db)
{
    char *err = 0;
    int rc = 0;
    // добавляем строку в таблицу Files
    const char* arrins [9] =
    {
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (1, 1, 1, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (1, 2, 0, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (1, 3, 0, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (2, 1, 0, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (2, 2, 1, 0)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (2, 3, 1, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (3, 1, 0, 1)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (3, 2, 1, 0)",
        "INSERT INTO Rules (id_u, id_f, C, E) VALUES (3, 3, 0, 1)"

    };
    //char buf[1024];
    //snprintf(buf, sizeof(buf), "INSERT INTO Rules (id_u, id_f, C, E) VALUES ('%d, %d, %d, %d,')", 1, 1, 1, 1);
    //char *ins = buf;

    for( int i = 0; i < 9; i++)
    {
        rc = sqlite3_exec(db, arrins[i], 0, 0, &err);
        if (rc != SQLITE_OK )
        {
            cout << "SQL error: " << err <<endl;
            return rc;
        }
    }

    /*rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return rc;
    }
    */
    return rc;
}

std::list<u_file> get_files (sqlite3 *db)
{
    std::list<u_file> Lfiles;
    char *err = 0;
    int rc = 0;
    const char *sel = "SELECT id_f, File_name FROM Files";

    rc = sqlite3_exec(db, sel, callback_file,(void*) &Lfiles, &err);
    cout << "Hi " << rc <<endl;
    if (rc != SQLITE_OK )
    {
        cout << "SQL error: get files" << err <<endl;
        return Lfiles;
    }
    return Lfiles;
};

int set_files(sqlite3 *db, QString *name_file, QString *text)
{
    QString a = *name_file;


    cout << a.toStdString() << " FILE_NAME" << endl;
    char *err = 0;
    int rc = 0;
    // добавляем строку в таблицу Files
    char buf[1024];
    snprintf(buf, sizeof(buf), "INSERT INTO Files (File_name) VALUES ('%s')", name_file->toStdString().c_str());
    char *ins = buf;

    rc = sqlite3_exec(db, ins, 0, 0, &err);

    if (rc != SQLITE_OK )
    {
        cout << "SQL error: " << err <<endl;
        return rc;
    }
    cout << "file inserted" << endl;

    QString folderPath = "Logs"; // Имя папки в проекте
    //QString fileName = "output.txt"; // Имя файла

    QDir projectDir = QDir::current(); // Получаем текущую директорию проекта
    projectDir.mkpath(folderPath); // Создаем папку, если её нет[citation:2]

    QString filePath = projectDir.absoluteFilePath(folderPath + QDir::separator() + *name_file + ".txt");
    cout << *text->toStdString().c_str() << " TEXT" << endl;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << *text;
        file.close();
    }

    return rc;
};

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
///Users
    const char *tableP = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, login INTEGER(4), password TEXT(30),full_name TEXT, phone INTEGER, email TEXT, adress_reg TEXT);";
    rc = sqlite3_exec(db, tableP, 0, 0, &err);

    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    cout << " PTABLE CREATED" << endl;
 ////Files
    const char *tableF = "CREATE TABLE IF NOT EXISTS Files(id_f INTEGER PRIMARY KEY AUTOINCREMENT, File_name TEXT(10), File_hash TEXT(30), Last_modif TEXT(30));";
    rc = sqlite3_exec(db, tableF, 0, 0, &err);

    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    cout << " FTABLE CREATED" << endl;
 ////Rules
    const char *tableRules = "CREATE TABLE IF NOT EXISTS Rules(id_r INTEGER PRIMARY KEY AUTOINCREMENT,id_u INTEGER REFERENCES Users(id) ON DELETE CASCADE,id_f INTEGER REFERENCES Files(id_f) ON DELETE CASCADE, C INTEGER(1), E INTEGER(1));";
    rc = sqlite3_exec(db, tableRules, 0, 0, &err);

    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << err <<endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    cout << " RTABLE CREATED" << endl;
///
    //insert_rules(db);
    QString abcd = "First";
    QString out = generate_hash(abcd.toStdString());
    cout << out.toStdString() << " -- out" << endl;
    return a.exec();
}
