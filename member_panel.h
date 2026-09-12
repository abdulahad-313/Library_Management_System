#ifndef MEMBER_PANEL_H
#define MEMBER_PANEL_H

#include <QWidget>

namespace Ui {
class Member_Panel;
}

class Member_Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Member_Panel(int memberId, QWidget *parent = nullptr);
    explicit Member_Panel(QWidget *parent = nullptr);
    int loggedInMemberId;
    void refreshMyBooksTable();
    ~Member_Panel();

private slots:
    void on_AllBook_clicked();

    void on_AddBook_clicked();

    void on_LogOut_clicked();

    void on_MyBook_clicked();

    void on_AllMembers_clicked();

    void on_ReturnBook_clicked();

private:
    Ui::Member_Panel *ui;
};

#endif // MEMBER_PANEL_H
