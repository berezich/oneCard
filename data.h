#ifndef DATA_H
#define DATA_H
#include "grp.h"
#include <QWidget>

class Data
{
public:
    Data();
    ~Data();

    QList<Grp> getLocalGroups();
private:

    QList<Grp> localGrpLst;

};

#endif // DATA_H
