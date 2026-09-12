#include "mainwindow.h"
#include "memberregistration.h"
#include "ui_mainwindow.h"
#include"librariyanlogin.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MemberLogin_clicked()
{
    s = new memberlogin(this);
    s->show();
}


void MainWindow::on_LibrariyanLogin_clicked()
{
    d = new LibrariyanLogin(this);
    d->show();
}


void MainWindow::on_Member_Registration_clicked()
{
    e=new MemberRegistration();
    e->show();
}

