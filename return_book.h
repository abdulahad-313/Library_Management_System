#ifndef RETURN_BOOK_H
#define RETURN_BOOK_H

#include <QDialog>

namespace Ui {
class Return_Book;
}

class Return_Book : public QDialog
{
    Q_OBJECT

public:
    explicit Return_Book(QWidget *parent = nullptr);
    ~Return_Book();

private slots:


    void on_Confirm_clicked();

private:
    Ui::Return_Book *ui;
};

#endif // RETURN_BOOK_H
