#ifndef SETTINGS_H
#define SETTINGS_H
#include "interface.h"
#include <QDataStream>
#include <QVariant>

enum OPTIONS{COLOR,LANGUAGE,GRP_VIEW};
class Settings
{
public:
    Settings();
    ~Settings();

    int skinColor()const{return _skinColor;}
    int lang()const{return _lang;}
    int grpView()const{return _grpView;}
    bool defEnterApp()const{return _defEnterApp;}
    QString login()const{return _login;}
    QString pass()const{return _pass;}
    QString endPoint()const{return _endPoint;}

    void setSkinColor(const int val){_skinColor = val;}
    void setLang(const int val){_lang = val;}
    void setGrpView(const int val){_grpView = val;}
    void setDefEnterApp(const bool val){_defEnterApp = val;}
    void setLogin(const QString val){_login = val;}
    void setPass(const QString val){_pass=val;}
    void setEndPoint(const QString val){_endPoint=val;}


private:
    int _skinColor;
    int _lang;
    int _grpView;
    bool _defEnterApp;

    QString _login;
    QString _pass;
    QString _endPoint;

    void init()
    {
        _skinColor = TEAL;
        _defEnterApp = false;
        _lang = RUSSIAN;
        _grpView = STANDART;
        _login = "oneCard";
        _pass = "123456";
        _endPoint = "http://onecard.bsv-grip.com";
    }
};
QDataStream& operator<<(QDataStream& out, const Settings& settings);
QDataStream& operator>>(QDataStream& in, Settings& settings);

#endif // SETTINGS_H
