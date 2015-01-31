#ifndef DATA_H
#define DATA_H
#include "grp.h"
#include "cardinfo.h"
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include "datalocationtype.h"
class Data
{
public:
    Data();
    ~Data();

    QList<Grp> getGroups(DATA_SOURCE src);
    QList<Grp> getLocalGroups();
    QList<CardInfo> *getLocalCards(int grpId);
    Grp *getLocalGrp(int grpId);
    CardInfo *getLocalCard(int grpId, int cardId);
    void saveImg(QString fromSrc, QString toSrc, QSize imgSaveSize, bool replace = true);
    void cacheLastImg(QString cacheFromDir, QString cacheToDir, int num, QSize imgSaveSize);
    QStringList getGrpImgSrc();
    void addNewGrp(QString name, QString grpImgSrc);

private:
    QString cameraDir;
    QList<Grp> localGrpLst;
    QList<Grp> serverGrpLst;
    QList<Grp> deviceGrpLst;

    QStringList grpImgSrcLst;
    void init()
    {
        cameraDir = "/storage/emulated/0/DCIM/camera/";
    }

};

#endif // DATA_H
