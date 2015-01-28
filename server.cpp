#include "server.h"

Server::Server(QObject *parent):QObject(parent)
{
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

void Server::onGrpLstDownloaded(QString fileName)
{
    grpLstTmp->clear();
    Grp *grp;
    qDebug() << "fileName = " << fileName;
    //QFile *file = new QFile("index2.html");
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit getGrpLstFinish(REQFILE_OPEN_ERR,ServerEror::errToString(REQFILE_OPEN_ERR));
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

        }if (token == QXmlStreamReader::StartElement)
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

        }
    }
    emit getGrpLstFinish(REQ_OK,ServerEror::errToString(REQ_OK));
}

void Server::onProcReqError(SERVER_ERRORS errCode, QString errMsg)
{
    httpManager.disconnect(SIGNAL(fileDownloaded));
    switch (reqType) {
    case GET_GRPS:
        emit getGrpLstFinish(errCode,errMsg);
        break;
    case GET_CARDS:
        emit getCardLstFinish(idGrp,NULL,errCode,errMsg);
        break;
    case GET_CARD_DATA:
        emit downloadCardDataFinish(idGrp,idCard,"","",errCode,errMsg);
        break;
    default:
        break;
    }
}

