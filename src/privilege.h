#ifndef PRIVILEGE_H
#define PRIVILEGE_H
#include <QtCore>
#include <QDebug>

class Privilege : public QObject
{
    Q_OBJECT
public:
    Privilege(int access = 0):access(access){}
    bool isAdmin()const{return access == 2;}
    bool isGuest()const{return access > 0;}
    int getAccess()const{return access; }
    void setAccess(int acc){access = acc;}
private:
    int access;
};

#endif // PRIVILEGE_H
