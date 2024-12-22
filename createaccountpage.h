#ifndef CREATEACCOUNTPAGE_H
#define CREATEACCOUNTPAGE_H

#include <QDialog>

namespace Ui {
class createaccountpage;
}

class createaccountpage : public QDialog
{
    Q_OBJECT

public:
    explicit createaccountpage(QWidget *parent = nullptr);
    ~createaccountpage();

private slots:
    // once this button is clicked it verifies the user credentials being asked to be created. if valid go if not reject.
    void on_pushButton_clicked();

    void on_backButton_clicked();

private:
    Ui::createaccountpage *ui;
};

#endif // CREATEACCOUNTPAGE_H
