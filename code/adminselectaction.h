#ifndef ADMINSELECTACTION_H
#define ADMINSELECTACTION_H

#include <QDialog>
#include "user.h"
#include "adminproxy.h"
#include "coursecatalog.h"

namespace Ui {
class adminSelectAction;
}

class adminSelectAction : public QDialog
{
    Q_OBJECT

public:
    explicit adminSelectAction(Admin* admin, QWidget *parent = nullptr);
    ~adminSelectAction();

private slots:

    void on_goCourses_clicked();

    void on_goStudents_clicked();

    void on_addConfirmCourse_2_clicked();

private:
    Admin* currentUser;
    Ui::adminSelectAction *ui;
};

#endif // ADMINSELECTACTION_H
