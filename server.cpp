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
    disconnect(&httpManager,SIGNAL(fileDownloaded(QString)),0,0);
    connect(&httpManager,SIGNAL(fileDownloaded(QString)),this,SLOT(onGrpLstDownloaded(QString)));
    httpManager.startdownloadFile(url);

}

void Server::getCardLstStart(int idGrpSrv)
{
    Grp *grp=NULL;
    reqType = GET_CARDS;
/*
    foreach (Grp igrp, grpLstTmp) {
        if(igrp.getIdSrv()==idGrp)
            grp=&igrp;
    }*/
    for (int i=0; i<grpLstTmp->length(); i++) {
        if((*grpLstTmp)[i].getIdSrv()==idGrpSrv)
        {
            grp=&(*grpLstTmp)[i];
            break;
        }
    }

    if(grp!=NULL)
    {
        if(grp->cardsLst!=NULL)
        {
            grp->cardsLst->clear();
            delete(grp->cardsLst);
            grp->cardsLst = NULL;
        }
    }
    else
    {
        emit getCardLstFinish(NO_GRP,ServerEror::errToString(NO_GRP));
        return;
    }
    idGrp = idGrpSrv;
    QString url = endPoint+"/?action=getcards&login="+login+"&pass="+pass+"&grpid="+QString::number(idGrpSrv);

    disconnect(&httpManager,SIGNAL(fileDownloaded(QString)),0,0);
    connect(&httpManager,SIGNAL(fileDownloaded(QString)),this,SLOT(onCardLstDownloaded(QString)));
    httpManager.startdownloadFile(url);
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
        else
        {
            grp->cardsLst = new QList<CardInfo>();
        }
    }


    //bool servErr = false;
    qDebug() << "onCardLstDownloaded: fileName = " << fileName;
    //QFile *file = new QFile("index2.html");
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit getCardLstFinish(REQFILE_OPEN_ERR,ServerEror::errToString(REQFILE_OPEN_ERR));
        delete(grp->cardsLst);
        grp->cardsLst = NULL;
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
                card->setIsImgLocal(false);
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "card"))
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
                            card->setCardIdGrpSrv(txt.toInt());
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
                grp->cardsLst->clear();
                delete(grp->cardsLst);
                grp->cardsLst = NULL;
                emit getCardLstFinish(WEB_SERVER_ERR,errMsg);
                return;
            }


        }
    }
    emit getCardLstFinish(REQ_OK,ServerEror::errToString(REQ_OK));
}

void Server::onGrpLstDownloaded(QString fileName)
{
    if(reqType!=GET_GRPS)
        return;
    grpLstTmp->clear();
    Grp *grp;
    //bool servErr = false;
    qDebug() << "onGrpLstDownloaded: fileName = " << fileName;
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
                            grp->setId(txt.toInt());
                            qDebug()<<txt;
                        }
                        if (xml.name().toString() == "ID_MOB")
                        {
                            //grp->setId(xml.readElementText().toInt());
                        }
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
                grp->cardsLst = NULL;
                grpLstTmp->append(*grp);
                delete(grp);
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

