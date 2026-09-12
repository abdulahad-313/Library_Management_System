#ifndef LIBRARIAN_PANAL_H
#define LIBRARIAN_PANAL_H

#include "addlibrarian.h"
#include "newbookadd.h"
#include "removebook.h"
#include "updatebook.h"
#include <QWidget>

namespace Ui {
class Librarian_panal;
}

class Librarian_panal : public QWidget
{
    Q_OBJECT

public:
    explicit Librarian_panal(QWidget *parent = nullptr);
    ~Librarian_panal();
    void refreshBooksTable();

private slots:
    void on_AllBook_clicked();

    void on_LogOut_clicked();

    void on_AddBook_clicked();

    void on_RemoveBook_clicked();

    void on_AddLibrarian_clicked();

    void on_AllMembers_clicked();

    void on_UpdateBook_clicked();

private:
    Ui::Librarian_panal *ui;
    NewBookAdd *i;
    RemoveBook *j;
    AddLibrarian *k;
    UpdateBook *l;
};

#endif // LIBRARIAN_PANAL_H
