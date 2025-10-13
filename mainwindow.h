#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QSettings>
#include <cstring>
#include <windows.h>
#include <winreg.h>
extern "C"
{
#include "sqlite3.h"
}
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

extern sqlite3 *db;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_EnterButton_clicked();

    void on_RegInButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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

int set_user(sqlite3 *db, User *user);
int callback(void *notUsed, int colCount, char **columns, char **colNames);
int callback_pas(void *notUsed, int colCount, char **columns, char **colNames);
int get_user (sqlite3 *db, int id, User *p_user);
int read_cfg(string *bios);
int write_cfg(string *bios);
void read_MachineGuide(string *bios);
int linking_computer(int* argc, char** argv);

int get_login (sqlite3 *db, int login, User *p_user);
int check_pass (sqlite3 *db, int login, User *p_user);
