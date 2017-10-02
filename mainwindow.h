#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connectDB.h"
#include <QMainWindow>
#include <QtSql>
#include <QSettings>
#include <QApplication>
#include <qobject.h>
#include <QItemSelectionModel>
#include <QtDebug>
#include <QSettings>
#include <QShortcut>
#include <QtWidgets>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTime>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void recordSelected();
    void on_startstop_clicked();
    void update_time();

private:
    Ui::MainWindow *ui;
    connectDB CDB;
    QString name;
    int id;
    QSqlTableModel *model;
    QModelIndex index;
    QTime counter;
    bool counting=FALSE;
    int hours,minutes;
    QString time_elapsed;
    int row;
    void update(void);
};

#endif // MAINWINDOW_H
