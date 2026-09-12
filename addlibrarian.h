#ifndef ADDLIBRARIAN_H
#define ADDLIBRARIAN_H

#include <QDialog>

namespace Ui {
class AddLibrarian;
}

class AddLibrarian : public QDialog
{
    Q_OBJECT

public:
    explicit AddLibrarian(QWidget *parent = nullptr);
    ~AddLibrarian();

private slots:
    void on_Confirm_clicked();

private:
    Ui::AddLibrarian *ui;
};

#endif // ADDLIBRARIAN_H
