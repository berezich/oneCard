#ifndef INTERFACE
#define INTERFACE
#include <QString>
#include <QList>

enum SKIN_COLOR_NAME{TEAL,CYAN,BLUE,DEEP_PURPLE,INDIGO,PINK,DEEP_ORANGE,GREEN,RED,BROWN,GRAY};
class SkinColor
{
    SKIN_COLOR_NAME _colorName;
    QString _head;
    QString _options;
public:
    SkinColor(SKIN_COLOR_NAME colorName, QString headColor, QString optionsColor)
    {
        _colorName = colorName;
        _head = headColor;
        _options = optionsColor;
    }
    QString head(){return _head;}
    QString options(){return _options;}
    SKIN_COLOR_NAME colorName(){return _colorName;}
};

class InterFace
{
    static QList<SkinColor> skins();
public:

    static SkinColor  getSkinColor(SKIN_COLOR_NAME color)
    {
        switch (color) {
        case RED:
            return SkinColor(RED,"#ef5350","#ef9a9a");
        case PINK:
            return SkinColor(PINK,"#ec407a","#f48fb1");
        case DEEP_PURPLE:
            return SkinColor(DEEP_PURPLE,"#7e57c2","#b39ddb");
        case INDIGO:
            return SkinColor(INDIGO,"#5c6bc0","#9fa8da");
        case BLUE:
            return SkinColor(BLUE,"#42a5f5","#90caf9");
        case CYAN:
            return SkinColor(CYAN,"#26c6da","#80deea");
        case TEAL:
            return SkinColor(TEAL,"#80bab7","#b2dfdb");
        case DEEP_ORANGE:
            return SkinColor(DEEP_ORANGE,"#ff7043","#ffab91");
        case GRAY:
            return SkinColor(GRAY,"#78909c","#b0bec5");
        case GREEN:
            return SkinColor(GREEN,"#66bb6a","#a5d6a7");
        case BROWN:
            return SkinColor(BROWN,"#8d6e63","#bcaaa4");


        default:
            break;
        }
    }

};
//QList<SkinColor> InterFace::skins = new QList<SkinColor>();

#endif // INTERFACE

