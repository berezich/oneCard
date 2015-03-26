#ifndef INTERFACE
#define INTERFACE
#include <QString>
#include <QList>
#include <QObject>


enum SKIN_COLOR_NAME{RED,PINK,DEEP_PURPLE,INDIGO,BLUE,TEAL,GREEN,DEEP_ORANGE,BROWN,GRAY};
enum LANGUAGES{RUSSIAN, ENGLISH};
enum GROUPS_VIEW{STANDART,NON_STANDART};
class SkinColor
{
    SKIN_COLOR_NAME _colorName;
    QString _head;
    QString _options;
    QString _normalName;
    QString _iconFolder;
public:
    SkinColor(SKIN_COLOR_NAME colorName, QString headColor, QString optionsColor, QString normalName, QString iconFolder)
    {
        _colorName = colorName;
        _head = headColor;
        _options = optionsColor;
        _normalName = normalName;
        _iconFolder = iconFolder;
    }
    QString head(){return _head;}
    QString options(){return _options;}
    SKIN_COLOR_NAME colorName(){return _colorName;}
    QString normalName(){return _normalName;}
    QString iconFolder(){return _iconFolder;}
};

class InterFace:public QObject
{
    Q_OBJECT
public:
    static SkinColor  getSkinColor(int color)
    {
        switch (color) {
        case RED:
            return SkinColor(RED,"#ef5350","#ef9a9a",tr("красный"),":/svg/tools/red/");
        case PINK:
            return SkinColor(PINK,"#ec407a","#e583a9",tr("розовый"),":/svg/tools/pink/");
        case DEEP_PURPLE:
            return SkinColor(DEEP_PURPLE,"#7e57c2","#a590d1",tr("фиолетовый"),":/svg/tools/deep_purple/");
        case INDIGO:
            return SkinColor(INDIGO,"#5c6bc0","#5c6bc0",tr("синий"),":/svg/tools/indigo/");
        case BLUE:
            return SkinColor(BLUE,"#42a5f5","#90caf9",tr("голубой"),":/svg/tools/indigo/");
        case TEAL:
            return SkinColor(TEAL,"#80bab7","#b2dfdb",tr("бирюзовый"),":/svg/tools/teal/");
        case GREEN:
            return SkinColor(GREEN,"#66bb6a","#9ecc9e",tr("зеленый"),":/svg/tools/green/");
        case DEEP_ORANGE:
            return SkinColor(DEEP_ORANGE,"#ff7043","#fca38b",tr("оранжевый"),":/svg/tools/orange/");
        case BROWN:
            return SkinColor(BROWN,"#8d6e63","#bcaaa4",tr("коричневый"),":/svg/tools/orange/");
        case GRAY:
            return SkinColor(GRAY,"#78909c","#b0bec5",tr("серый"),":/svg/tools/orange/");


        default:
            return SkinColor(TEAL,"#80bab7","#b2dfdb",tr("бирюзовый"),":/svg/tools/orange/");
        }
    }
    static QString getGrpViewFolder(int view)
    {
        switch (view) {
        case STANDART:
            return ":/svg/grpIcons/standart/";
        case NON_STANDART:
            return ":/svg/grpIcons/non_standart/";
        default:
            return "";
        }
    }
    static QString getGrpViewName(int view)
    {
        switch (view) {
        case STANDART:
            return tr("стандартный");
        case NON_STANDART:
            return tr("нестандартный");
        default:
            return "";
        }
    }

};

class Languages:public QObject
{
    Q_OBJECT
public: static QString getLangName(int lang)
    {
        switch (lang) {
        case ENGLISH:
            return tr("английский");
        case RUSSIAN:
            return tr("русский");
        default:
            return "";
        }
    }
static QString getLangTs(int lang)
    {
        switch (lang) {
        case ENGLISH:
            return ":/onecard_en";
        case RUSSIAN:
            return ":/onecard_ru";
        default:
            return "";
        }
    }
};

#endif // INTERFACE

