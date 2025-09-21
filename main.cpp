#include "mainwindow.h"
#include <stdio.h>
extern "C" {
#include "sqlite3.h"
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    sqlite3 *db;    // указатель на базу данных
    // открываем подключение к базе данных
    int result  = sqlite3_open("test.db", &db);
    printf("result = %d\n", result);
    // закрываем подключение
    sqlite3_close(db);
    return a.exec();
}
