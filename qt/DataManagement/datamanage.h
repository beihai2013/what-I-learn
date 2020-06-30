#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QMainWindow>
#include <QSqlTableModel>
QT_BEGIN_NAMESPACE
namespace Ui { class DataManage; }
QT_END_NAMESPACE

class DataManage : public QMainWindow
{
    Q_OBJECT

public:
    DataManage(QWidget *parent = nullptr);
    ~DataManage();

private:
    Ui::DataManage *ui;
    QSqlTableModel *model;
    int id;

private slots:
    void insert();
    void find();
    void deleteByChoose();
    void showAll();
    void submitRevise();
    void removeAlter();
};
#endif // DATAMANAGE_H
