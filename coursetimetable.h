#ifndef COURSETIMETABLE_H
#define COURSETIMETABLE_H

#include <QDialog>
#include "user.h"

namespace Ui {
class courseTimetable;
// this is a screen which displays the course selection for fall and winter terms
}

class courseTimetable : public QDialog
{
    Q_OBJECT

public:
    explicit courseTimetable(User* user, QWidget *parent = nullptr);
    ~courseTimetable();

private slots:

    void on_back_clicked();

private:
    //takes current user which is passed through to display their timetable
    User* currentUser;
    Ui::courseTimetable *ui;
};

#endif // COURSETIMETABLE_H
