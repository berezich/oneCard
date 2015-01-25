#include "server.h"

Server::Server(QObject *parent):QObject(parent)
{
    grpLstTmp = new QList<Grp>();
    connect(&httpManager,SIGNAL(fileErrDownload(int, QString)),this,SLOT(onProcReqError(int, QString)));
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
    httpManager.disconnect(SIGNAL(fileDownloaded));
    httpManager.disconnect(SIGNAL(fileErrDownload));

    QString url = endPoint+"/?action=getgrp&login="+login+"&pass="+pass;
    httpManager.startdownloadFile(url);

    connect(&httpManager,SIGNAL(fileDownloaded(QFile*)),this,SLOT(onGrpLstDownloaded(QFile*)));

}

void Server::onGrpLstDownloaded(QFile *fileResponse)
{
    grpLstTmp->clear();
    Grp *grp;
    QXmlStreamReader xml(fileResponse);
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "groups")
                continue;
            if (xml.name() == "grp")
            {
                grp = new Grp();
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "etap"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name() == "ID")
                            grp->setIdSrv(xml.text().toInt());
                        if (xml.name() == "ID_MOB")
                            grp->setId(xml.text().toInt());
                        if (xml.name() == "NAME")
                            grp->setName(xml.text().toString());
                        if (xml.name() == "ICON_ID")
                            grp->setImgSrc(xml.text().toString());
                    }
                    xml.readNext();
                }
                grpLstTmp->append(*grp);
            }

        }
    }
    emit getGrpLstFinish(grpLstTmp,-1,"OK");
}

void Server::onProcReqError(int errCode, QString errMsg)
{
    switch (reqType) {
    case GET_GRPS:
        emit getGrpLstFinish(NULL,errCode,errMsg);
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

