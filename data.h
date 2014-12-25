#ifndef DATA_H
#define DATA_H
#include "grp.h"
#include "cardinfo.h"
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QDir>

class Data
{
public:
    Data();
    ~Data();

    QList<Grp> getLocalGroups();
    QList<CardInfo> *getLocalCards(int grpId);
    Grp *getLocalGrp(int grpId);
    CardInfo *getLocalCard(int grpId, int cardId);
    void saveImg(QString fromSrc, QString toSrc, QSize imgSaveSize);
    void cacheLastImg(QString cacheFromDir, QString cacheToDir, int num, QSize imgSaveSize);

private:
    QString cameraDir = "/storage/emulated/0/DCIM/camera/";
    QList<Grp> localGrpLst;

};

#endif // DATA_H