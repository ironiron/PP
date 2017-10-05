#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectDB.h"


QSettings settings ("MySoft", "PP");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("DATA");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(TRUE);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->selectRow(0);
    recordSelected();
    QItemSelectionModel *select = ui->tableView->selectionModel();
    connect(select, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(recordSelected()));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
    timer->start(60000);// 1 minute

}

MainWindow::~MainWindow()
{
    delete ui;
}

//adding new task
void MainWindow::on_addButton_clicked()
{
    name=ui->lineEdit->text();
    ui->lineEdit->clear();
    id = settings.value("id",0).toInt();
    CDB.add(id,name,"00:00");
    id++;
    settings.setValue("id",id);
    update();
}

void MainWindow::recordSelected()
{
   index = ui->tableView->currentIndex();
   row = index.row();
   ui->label->setText(ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString());
   ui->lcdNumber->display("00:00");
}

void MainWindow::on_startstop_clicked()
{
    ui->lcdNumber->display("00:00");

    if (counting)
    {
        counting=FALSE;
        hours=minutes/60;
        minutes=minutes%60;
        id=ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toInt();
        CDB.update(id,hours,minutes);
        update();

        ui->startstop->setText("START");
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->lineEdit->setEnabled(TRUE);
        ui->addButton->setEnabled(TRUE);
    }
    else
    {
        counting=TRUE;
        minutes=0;
        counter.start();

        ui->startstop->setText("STOP");
        ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->lineEdit->setEnabled(FALSE);\
        ui->addButton->setEnabled(FALSE);
    }
}

//update visible records in table
void MainWindow::update(void)
{
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setFocus();
    ui->tableView->selectRow(row);
    model->submit();
}

//counting time. this function is called every 1 minute.
void MainWindow::update_time(void)
{
    minutes++;
    if (minutes<10)//force 2 digit note
        time_elapsed=QString::number(minutes/60)+":0"+QString::number(minutes%60);
    else
        time_elapsed=QString::number(minutes/60)+":"+QString::number(minutes%60);
    ui->lcdNumber->display(time_elapsed);
}
