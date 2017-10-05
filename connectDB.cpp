#include "connectDB.h"

connectDB::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Base");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        exit(1);
    }

    QSqlQuery dada(db);
    query=dada;
    query.exec("create table DATA ("
               "id int primary key,"
               "name varchar(30), "
               "time varchar(30))");
}

void connectDB::add(int id,QString name, QString time)
{
    QString i = QString::number(id);
    query.exec("insert into DATA values('"+i+"','"+name+"', '"+time+"')");
}

void connectDB::update(int id,int hours,int minutes)
{
    query.prepare("select time from DATA where id=:id");//get old value
    query.bindValue(":id",id);
    query.exec();
    while (query.next()) string=query.value(0).toString();

    minutes=minutes+string.section(':',1,1).toInt();//get number from string
    hours=hours+string.section(':',0,0).toInt();
    hours=hours+minutes/60;
    minutes=minutes%60;
    //make string again
    if (minutes<10)//force 2 digit note
        string=QString::number(hours)+":0"+QString::number(minutes);
    else
        string=QString::number(hours)+":"+QString::number(minutes);

    query.prepare("update DATA set time=:time where id=:id");
    query.bindValue(":time",string);
    query.bindValue(":id",id);
    query.exec();
}



