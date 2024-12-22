#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QDialog>
#include "user.h"

namespace Ui {
class notifications;
}

class notifications : public QDialog
{
    Q_OBJECT

public:
    explicit notifications(User* user, QWidget *parent = nullptr);
    ~notifications();

private slots:
    void on_back_clicked();

private:
    User* currentUser;
    Ui::notifications *ui;
};

#endif // NOTIFICATIONS_H
