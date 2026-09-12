#ifndef UPDATEBOOK_H
#define UPDATEBOOK_H

#include <QDialog>

namespace Ui {
class UpdateBook;
}

class UpdateBook : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateBook(QWidget *parent = nullptr);
    ~UpdateBook();

private slots:
    void on_Confirm_clicked();

    void on_OK_clicked();

private:
    Ui::UpdateBook *ui;
};

#endif // UPDATEBOOK_H
