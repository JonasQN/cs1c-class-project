#include "login.h"
#include "privilege.h"
#include "MainWindow.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

/**
 * @brief Login::signinUser - Checking username and password from database
 * @param username
 * @param password
 * @param accessLevel
 * @return
 * - 0: Invalid account
 * - 1: Guest account
 * - 2: Admin account
 */
int Login::loginUser(QString username, QString password)
{
    QString homePath = QFileInfo(".").absolutePath();
    // Open the database file to read user info
    QFile databaseFile(homePath + dataFileName);
    if(!databaseFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, ":C", "User File not found!!!");
        return 0;
    }

    QTextStream input(&databaseFile);
    QString user, pass;
    int level;
    while(!input.atEnd())
    {
        // Read user and password to check
        input >> user >> pass >> level;
        // Check this is mapping or not
        if(user == username && pass == password)
        {
            databaseFile.close();
            return level;
        }
    }
    databaseFile.close();
    return 0; // Invalid account
}

/**
 * @brief Login::signinUser - Sigin user function
 * @param username
 * @param password
 * @param accessLevel
 * @return
 * - 0: Data file not found.
 * - 1: Duplicate username.
 * - 2: sigin success
 */
int Login::signinUser(QString username, QString password, int accessLevel)
{
    QString homePath = QFileInfo(".").absolutePath();
    // Open the database file to read user info
    QFile databaseFile(homePath + dataFileName);
    if(databaseFile.open(QFile::ReadOnly | QFile::Text))
    {
        // Check duplicate file
        QTextStream input(&databaseFile);
        QString user, pass;
        int level;

        while(!input.atEnd())
        {
            // Read user and password to check
            input >> user >> pass >> level;
            // Check this is mapping or not
            if(user == username)
            {
                databaseFile.close();
                return 1;
            }
        }
        databaseFile.close();
    }

    //  If no duplicates, reopen to append new data to file
    databaseFile.open(QFile::WriteOnly | QFile::Append);

    QTextStream output(&databaseFile);
    output << username << " " << password << " " << accessLevel << endl;
    databaseFile.close();
    return 2;
}

void Login::on_pushButton_addUser_clicked()
{
    QString username = ui->lineEdit_addUser->text();
    QString password = ui->lineEdit_addPass->text();
    int access = ui->checkBox_admin->isChecked() + 1;


    ui->lineEdit_addPass->setText("");
    if(password.length() < 8){
        QMessageBox::warning(this, "Error", "Password is too short!");
        return;
    }
    else if(username.length() < 1){
        QMessageBox::warning(this, "Error", "Enter a username!");
        return;
    }

    int checkIn = signinUser(username, password, access);
    if(checkIn == 2){
        QMessageBox::information(this, "Add User", "Create user successfuly");
        //auth.setAccess(access);
    }
    else if(checkIn == 1){
        QMessageBox::warning(this, "Error", "Username is already taken!");
    }
}

void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    int access = loginUser(username, password);
    if(access==0){
        QMessageBox::information(this, "Login", "Invalid username or password");
    }else if (access==1) {
        QMessageBox::information(this, "Login", "Welcome guest user!");
        //auth.setAccess(access);
        w.callSetAdmin(false);
        w.show();
        this->close();
    }else if (access==2) {
        QMessageBox::information(this, "Login", "Welcome admin!");
        //auth.setAccess(access);
        w.callSetAdmin(true);
        w.show();
        this->close();
    }else {
        QMessageBox::warning(this, "Error!", "You broke the program?");
    }

}
