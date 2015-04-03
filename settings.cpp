#include "settings.h"

Settings::Settings()
{
    init();
}

Settings::~Settings()
{

}

QDataStream &operator<<(QDataStream &out, const Settings &settings)
{
    out << settings.skinColor() << settings.lang() << settings.grpView() << settings.defEnterApp() << settings.login() << settings.pass() << settings.endPoint();
    return out;
}

QDataStream &operator>>(QDataStream &in, Settings &settings)
{
    int iVal;
    in >> iVal;
    settings.setSkinColor(iVal);
    in >> iVal;
    settings.setLang(iVal);
    in >> iVal;
    settings.setGrpView(iVal);
    bool bVal;
    in >> bVal;
    settings.setDefEnterApp(bVal);
    QString sVal;
    in >> sVal;
    settings.setLogin(sVal);
    in >> sVal;
    settings.setPass(sVal);
    in >> sVal;
    settings.setEndPoint(sVal);
    return in;

}

