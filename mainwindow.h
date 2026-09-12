#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"memberlogin.h"
#include"librariyanlogin.h"
#include"memberregistration.h"
#include <QMainWindow>
#include<QtSql>
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:

    void on_MemberLogin_clicked();

    void on_LibrariyanLogin_clicked();

    void on_Member_Registration_clicked();

private:
    Ui::MainWindow *ui;
    memberlogin *s;
    LibrariyanLogin *d;
    MemberRegistration *e;
};
#endif // MAINWINDOW_H
