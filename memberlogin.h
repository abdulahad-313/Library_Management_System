#ifndef MEMBERLOGIN_H
#define MEMBERLOGIN_H
#include"member_panel.h"

#include <QDialog>
#include <qsqldatabase.h>

namespace Ui {
class memberlogin;
}

class memberlogin : public QDialog
{
    Q_OBJECT

public:
    explicit memberlogin(QWidget *parent = nullptr);
    ~memberlogin();

private slots:
    void on_Confirm_clicked();

private:
    Ui::memberlogin *ui;
    QSqlDatabase db;
    Member_Panel *f;
};

#endif // MEMBERLOGIN_H
