#ifndef NEWBOOKADD_H
#define NEWBOOKADD_H

#include <QDialog>

namespace Ui {
class NewBookAdd;
}

class NewBookAdd : public QDialog
{
    Q_OBJECT

public:
    explicit NewBookAdd(QWidget *parent = nullptr);
    ~NewBookAdd();

private slots:


    void on_Confirm_clicked();

private:
    Ui::NewBookAdd *ui;
};

#endif // NEWBOOKADD_H
