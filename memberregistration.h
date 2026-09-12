#ifndef MEMBERREGISTRATION_H
#define MEMBERREGISTRATION_H

#include <QDialog>
#include <QMainWindow>
#include<QtSql>
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>

namespace Ui {
class MemberRegistration;
}

class MemberRegistration : public QDialog
{
    Q_OBJECT

public:
    explicit MemberRegistration(QWidget *parent = nullptr);
    ~MemberRegistration();

private slots:

    void on_pushButton_MR_clicked();

private:
    Ui::MemberRegistration *ui;
     QSqlDatabase db;
};

#endif // MEMBERREGISTRATION_H
