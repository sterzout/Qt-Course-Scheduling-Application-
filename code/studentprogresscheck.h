#ifndef STUDENTPROGRESSCHECK_H
#define STUDENTPROGRESSCHECK_H

#include <QDialog>
#include "user.h"
#include "coursecatalog.h"

namespace Ui {
class studentProgressCheck;
}

class studentProgressCheck : public QDialog
{
    Q_OBJECT

public:
    explicit studentProgressCheck(User* user, QWidget *parent = nullptr);
    ~studentProgressCheck();

private slots:
    void on_addConfirmCourse_2_clicked();

    void on_back_clicked();

    void on_calculateProgress_clicked();

private:
    CourseCatalog* courseCatalog;
    User* currentUser;
    Ui::studentProgressCheck *ui;
};

#endif // STUDENTPROGRESSCHECK_H
