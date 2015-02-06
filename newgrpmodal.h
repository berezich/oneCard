#ifndef NEWGRPMODAL_H
#define NEWGRPMODAL_H
#include "overlay.h"
#include "QVBoxLayout"
#include <QPainter>
#include <QLineEdit>
#include <QPoint>
#include <QLabel>
#include <QtCore/qmath.h>
#include "simpleicon.h"
class NewGrpModal : public Overlay
{
    Q_OBJECT
public:
    NewGrpModal(QSize size, double scale,QStringList grpIconLst, QString grpViewFolder,QWidget *parent = 0);
    ~NewGrpModal();
    void setIconLst();

protected:

    void paintEvent(QPaintEvent *event);
private slots:
    void onClickGrpIcon(int i);
    void onClickGrpOk();
    void onClickGrpCancel();
signals:
    void newGrpConfigured(QString name, QString src);
private:

    int columnsNum;
    int rowsNum;
    QSize iconSize;
    QSize iconOkSize;
    QSize screenSize;
    int gridSpace;

    QVBoxLayout *formBasic;
    QVBoxLayout *formLayout;
    QString backGroundColor;
    double scaleFactor;
    double lblTxtSize;
    QString lblTxtColor;
    QPoint rectPoint;
    QSize rectSize;
    qreal xRound;
    qreal yRound;
    QWidget *formWidget;
    QString lbl1;
    QString lbl2;
    QLabel *nameLbl;
    QLabel *choiceLbl;
    QLineEdit *grpName;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    QStringList imgSrcLst;
    QString grpViewFolder;
    QList<SimpleIcon *> iconsGrid;
    int selectedIcon;
    void init()
    {
        columnsNum = 3;
        rowsNum = 4;
        iconSize = QSize(135,135)*0.985;
        iconOkSize = QSize(120,60);
        screenSize = QSize(720,1280);
        gridSpace = 30;
        backGroundColor = "#e5e5e5";
        scaleFactor = 1;
        lblTxtSize = 18;
        lblTxtColor = "#000000";
        rectSize = QSize(630,907);
        xRound = 40;
        yRound = 40;
        lbl1 = "Название группы";
        lbl2 = "Выберите иконку";
        selectedIcon=-1;
    }
};

#endif // NEWGRPMODAL_H
