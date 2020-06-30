#include "datamanage.h"
#include "ui_datamanage.h"
#include <sqlutils.h>
#include <QtSql>
#include <string.h>
#include <QMessageBox>
#include <QDebug>

DataManage::DataManage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataManage)
{
    ui->setupUi(this);
    // 判断是否有sqlite数据库
    if (!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(
                    this,
                    "Unable to load database",
                    "This demo needs the MYSQL driver"
                    );

    if (initDb() == false)
        return;

    model = new QSqlTableModel(this);
    model->setTable("data");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    ui->tableView->setModel(model);
    QSqlQuery q;
    // initialize id to the max id in the table
    id = model->index(model->rowCount() - 1, 0).data().toInt() + 1;

    connect(ui->insertBtn, &QPushButton::clicked, this, &DataManage::insert);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &DataManage::deleteByChoose);
    connect(ui->findBtn, &QPushButton::clicked, this, &DataManage::find);
    connect(ui->showAllBtn, &QPushButton::clicked, this, &DataManage::showAll);
    connect(ui->submitAlterBtn, &QPushButton::clicked, this, &DataManage::submitRevise);
    connect(ui->removeAlterBtn, &QPushButton::clicked, this, &DataManage::removeAlter);
}

DataManage::~DataManage()
{
    delete ui;
}
void DataManage::removeAlter(){
    model->revertAll();
}
void DataManage::submitRevise()
{
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) {
       model->database().commit(); //提交
    } else {
       model->database().rollback(); //回滚
       QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(model->lastError().text()));
    }
}
void DataManage::insert()
{
    int rowNum = model->rowCount();
    model->insertRow(rowNum);
    model->setData(model->index(rowNum, 0), id++);
}
void DataManage::deleteByChoose(){
    int curRow = ui->tableView->currentIndex().row();

    model->removeRow(curRow);
    int ok = QMessageBox::warning(this, tr("删除当前行!"), tr("你确定删除当前行嘛"),
                                  QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::No) {
        model->revertAll();
    }
    else {
        model->submitAll();
    }
}
void DataManage::find(){
    QString name = ui->findName->text();
    qint16 minYear = qint16(ui->findMinYear->text().toInt());
    qint16 maxYear = qint16(ui->findMaxYear->text().toInt());
    if (ui->findMinYear->text() != "" and ui->findMaxYear->text() != "") {
        model->setFilter(QString("name = '%1' and year >= '%2' and year <= '%3'").arg(name, minYear, maxYear));
        qDebug() << "first";
    } else {
        model->setFilter(QString("name = '%1'").arg(name));
        qDebug() << "second";
    }
    model->select();

}
void DataManage::showAll(){
    model->setTable("data");
    model->select();
}
