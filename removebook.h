#ifndef REMOVEBOOK_H
#define REMOVEBOOK_H

#include <QDialog>

namespace Ui {
class RemoveBook;
}

class RemoveBook : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveBook(QWidget *parent = nullptr);
    ~RemoveBook();

private slots:
    void on_Confirm_clicked();

private:
    Ui::RemoveBook *ui;
};

#endif // REMOVEBOOK_H
