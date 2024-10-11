#ifndef WRITERDATA_H
#define WRITERDATA_H

#include <QFile>
#include <QDir>

#include <QDomDocument>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QBuffer>

#include "filedir.h"

//for saving data
#include "common/stashdata.h"
extern stashdata *stash;
//for restore data
#include "common/factorydata.h"
extern factorydata *factory;

#include <QObject>

class writerdata : public QObject{
    Q_OBJECT

public:
    writerdata(){}
    ~writerdata(){}

    void writeData(QString file, QByteArray ba);
    QByteArray readData(QString file);

    void saveData(QString path);
    void loadData(QString path);
    void removeData(QString path);
    void saveToLocal(QVector<int> rac,
                     QString path,
                     QByteArray m,
                     QByteArray p,
                     QByteArray e,
                     QByteArray s);

    QByteArray svg(QByteArray map);
    QByteArray extend();

    bool isEmptyTMP(QString path);
    bool isEmptyCurrent();

    QJsonObject getData();
    void setData(QJsonObject data);

private:
    QVector<QDomDocument> getDomElements();
};

#endif // WRITERDATA_H
