#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QApplication>
#include <qstandardpaths.h>
#include <qobject.h>

class connectDB : public QSqlDatabase
{
     QSqlQuery query;
     QString string;
public:
     connectDB();  
     void add(int id, QString name, QString time);
     void update(int id, int hours, int minutes);
};

#endif // CONNECTDB_H
