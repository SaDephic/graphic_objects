#ifndef STATEAUTH_H
#define STATEAUTH_H

#include <QObject>

class stateauth : public QObject{
    Q_OBJECT

public:
    QString user;
    bool state;
    QVector<QString> permissions;
    int region;
    QVector<int> areas;

public:
    stateauth();
    ~stateauth();

    void setUser(QString _user);
    void setStatesAuth(bool _state);
    void setPrevileges(QVector<QString> _permissions);
    void setRegion(int _region);
    void setAreas(QVector<int> _areas);

    QString areas_text();
    QString permissions_text();
    QString uperm();
};

#endif // STATEAUTH_H
