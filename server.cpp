#include "server.h"

Server::Server(QObject *parent):QObject(parent)
{
    init();
    grpLstTmp = new QList<Grp>();
    connect(&httpManager,SIGNAL(fileErrDownload(SERVER_ERRORS, QString)),this,SLOT(onProcReqError(SERVER_ERRORS, QString)));
}

Server::~Server()
{

}

void Server::setEndPoint(QString ip, int port, QString path)
{
    endPoint = (ip.startsWith("http://",Qt::CaseInsensitive) ? ip :  "http://"+ip )+((port!=-1)?":"+port : "")+((path!="")? "/"+path : "");

}

void Server::getGrpLstStart()
{
    reqType = GET_GRPS;
    QString url = endPoint+"/?action=getgrp&login="+login+"&pass="+pass;
    httpManager.startdownloadFile(url);

    connect(&httpManager,SIGNAL(fileDownloaded(QString)),this,SLOT(onGrpLstDownloaded(QString)));
}

void Server::getCardLstStart(int idGrpSrv)
{
    Grp *grp=NULL;
/*
    foreach (Grp igrp, grpLstTmp) {
        if(igrp.getIdSrv()==idGrp)
            grp=&igrp;
    }*/
    for (int i=0; i<grpLstTmp->length(); i++) {
        if((*grpLstTmp)[i].getIdSrv()==idGrpSrv)
            grp=&(*grpLstTmp)[i];
    }

    if(grp!=NULL)
    {
        grp->cardsLst->clear();
        delete(grp->cardsLst);
        grp->cardsLst = NULL;
    }
    else
    {
        emit getGrpLstFinish(NO_GRP,ServerEror::errToString(NO_GRP));
        return;
    }
    reqType = GET_CARDS;
    idGrp = idGrpSrv;
    QString url = endPoint+"/?action=getcards&login="+login+"&pass="+pass+"&grpid="+idGrpSrv;
    httpManager.startdownloadFile(url);

    connect(&httpManager,SIGNAL(fileDownloaded(QString)),this,SLOT(onCardLstDownloaded(QString)));
}

Grp *Server::getGrpTmp(int grpIdSrv)
{

    for (int i=0; i<grpLstTmp->length(); i++) {
        if((*grpLstTmp)[i].getIdSrv()==grpIdSrv)
            return &(*grpLstTmp)[i];
    }

    return NULL;
}

void Server::onCardLstDownloaded(QString fileName)
{

    CardInfo *card;

    Grp *grp=NULL;
    for (int i=0; i<grpLstTmp->length(); i++) {
        if((*grpLstTmp)[i].getIdSrv()==idGrp)
            grp=&(*grpLstTmp)[i];
    }
    if(grp!=NULL)
    {
        if(grp->cardsLst!=NULL)
            grp->cardsLst->clear();
    }

    //bool servErr = false;
    qDebug() << "fileName = " << fileName;
    //QFile *file = new QFile("index2.html");
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit getCardLstFinish(REQFILE_OPEN_ERR,ServerEror::errToString(REQFILE_OPEN_ERR));
        _isGrpLstDownloaded = false;
        delete file;
        file = 0;
        return;
    }

    QXmlStreamReader xml(file);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            qDebug() << "Encoding: " << xml.documentEncoding().toString() ;
            continue;

        }
        if (token == QXmlStreamReader::StartElement)
        {
            qDebug() << "xml curElem name = " << xml.name();
            if (xml.name() == "cards")
                continue;
            if (xml.name() == "card")
            {
                card = new CardInfo();
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "grp"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name().toString() == "ID")
                        {
                            QString txt = xml.readElementText();
                            card->setCardIdSrv(txt.toInt());
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "ID_MOB")
                        {
                            QString txt = xml.readElementText();
                            if(txt!="")
                                card->setCardId(txt.toInt());
                        }
                        if (xml.name().toString() == "GRP_ID")
                        {
                            QString txt = xml.readElementText();
                            card->setCardGrpId(txt.toInt());
                        }

                        if (xml.name().toString() == "NAME")
                        {
                            QString txt = xml.readElementText();
                            card->setCardName(txt);
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "F_IMG")
                        {
                            QString txt = xml.readElementText();
                            card->setCardImgSrc(txt);
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "B_IMG")
                        {
                            QString txt = xml.readElementText();
                            card->setCardImgBackSrc(txt);
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "IS_MAGNET")
                        {
                            QString txt = xml.readElementText();
                            if(txt.toInt()>0)
                                card->setFlagMagnetLine(true);
                            else
                                card->setFlagMagnetLine(false);
                        }
                        if (xml.name().toString() == "MAGNET")
                        {
                            QString txt = xml.readElementText();
                            card->setMagnet(txt);
                        }
                    }
                    xml.readNext();
                }
                grp->cardsLst->append(*card);
                delete(card);
            }
            if(xml.name() == "err")
            {
                int errCode;
                QString errMsg;
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "err"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name().toString() == "code")
                        {
                            errCode = xml.readElementText().toInt();
                            qDebug()<<errCode;
                        }
                        if (xml.name().toString() == "msg")
                        {
                            errMsg  = xml.readElementText();
                            qDebug()<<errMsg;

                        }

                    }
                    xml.readNext();
                }
                emit getCardLstFinish(WEB_SERVER_ERR,errMsg);
                grp->cardsLst->clear();
                return;
            }


        }
    }
    emit getCardLstFinish(REQ_OK,ServerEror::errToString(REQ_OK));
}

void Server::onGrpLstDownloaded(QString fileName)
{
    grpLstTmp->clear();
    Grp *grp;
    //bool servErr = false;
    qDebug() << "fileName = " << fileName;
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit getCardLstFinish(REQFILE_OPEN_ERR,ServerEror::errToString(REQFILE_OPEN_ERR));
        delete file;
        file = 0;
        return;
    }

    QXmlStreamReader xml(file);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            qDebug() << "Encoding: " << xml.documentEncoding().toString() ;
            continue;

        }
        if (token == QXmlStreamReader::StartElement)
        {
            qDebug() << "xml curElem name = " << xml.name();
            if (xml.name() == "groups")
                continue;
            if (xml.name() == "grp")
            {
                grp = new Grp();
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "grp"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name().toString() == "ID")
                        {
                            QString txt = xml.readElementText();
                            grp->setIdSrv(txt.toInt());
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "ID_MOB")
                            grp->setId(xml.readElementText().toInt());
                        if (xml.name().toString() == "NAME")
                        {
                            QString txt = xml.readElementText();
                            grp->setName(txt);
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "ICON")
                        {
                            QString txt = ":/svg/grpIcons/"+xml.readElementText();
                            qDebug()<<txt;
                            grp->setImgSrc(txt);
                        }
                    }
                    xml.readNext();
                }
                grpLstTmp->append(*grp);
            }
            if(xml.name() == "err")
            {
                int errCode;
                QString errMsg;
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "err"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name().toString() == "code")
                        {
                            errCode = xml.readElementText().toInt();
                            qDebug()<<errCode;
                        }
                        if (xml.name().toString() == "msg")
                        {
                            errMsg  = xml.readElementText();
                            qDebug()<<errMsg;

                        }

                    }
                    xml.readNext();
                }
                _isGrpLstDownloaded = false;
                emit getGrpLstFinish(WEB_SERVER_ERR,errMsg);
                grpLstTmp->clear();
                return;
            }


        }
    }
    _isGrpLstDownloaded = true;
    emit getGrpLstFinish(REQ_OK,ServerEror::errToString(REQ_OK));
}

void Server::onProcReqError(SERVER_ERRORS errCode, QString errMsg)
{
    httpManager.disconnect(SIGNAL(fileDownloaded));
    switch (reqType) {
    case GET_GRPS:
        _isGrpLstDownloaded=false;
        emit getGrpLstFinish(errCode,errMsg);
        break;
    case GET_CARDS:
        emit getCardLstFinish(errCode,errMsg);
        break;
    case GET_CARD_DATA:
        emit downloadCardDataFinish(idGrp,idCard,"","",errCode,errMsg);
        break;
    default:
        break;
    }
}

