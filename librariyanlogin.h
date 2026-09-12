#ifndef LIBRARIYANLOGIN_H
#define LIBRARIYANLOGIN_H
#include"librarian_panal.h"

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class LibrariyanLogin;
}

class LibrariyanLogin : public QDialog
{
    Q_OBJECT

public:
    explicit LibrariyanLogin(QWidget *parent = nullptr);
    ~LibrariyanLogin();

private slots:
    void on_Confirm_clicked();

private:
    Ui::LibrariyanLogin *ui;
    Librarian_panal *g;
    QSqlDatabase db;
};

#endif // LIBRARIYANLOGIN_H
