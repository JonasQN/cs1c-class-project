#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "privilege.h"
#include "MainWindow.h"
extern Privilege auth;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    int loginUser(QString username, QString password);
    int signinUser(QString username, QString password, int accessLevel);

private slots:
    void on_pushButton_addUser_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QString dataFileName = "users.txt";
    MainWindow w;
};

#endif // LOGIN_H
