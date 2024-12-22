#ifndef LOGINORCREATE_H
#define LOGINORCREATE_H

#include <QDialog>

namespace Ui {
class loginorcreate;
}

class loginorcreate : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit loginorcreate(QWidget *parent = nullptr);
    ~loginorcreate();
private slots:
    // login, createaccount or exit program. To exit you logout and then when you do you can exit from main screen.
    // may add some other exits later on
    void on_loginbutton_clicked();

    void on_createbutton_clicked();


    void on_programexitbutton_clicked();


private:
    Ui::loginorcreate *ui;
};

#endif // LOGINORCREATE_H
