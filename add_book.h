#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QDialog>

namespace Ui {
class Add_Book;
}

class Add_Book : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Book(QWidget *parent = nullptr);
    ~Add_Book();

private slots:
    void on_Confirm_clicked();

private:
    Ui::Add_Book *ui;
};

#endif // ADD_BOOK_H
