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
public:
    NewGrpModal(QSize size, double scale,QStringList grpIconLst, QWidget *parent = 0);
    ~NewGrpModal();
    void setIconLst();

protected:

    void paintEvent(QPaintEvent *event);
private slots:
    void onClickGrpIcon(int i);
    void onClickGrpCreated();
signals:
    //void newGrpConfigured(QString name, QString src);
private:

    int columnsNum = 3;
    int rowsNum = 4;
    QSize iconSize = QSize(140,140);
    QSize iconOkSize = QSize(140,70);
    QSize screenSize = QSize(720,1280);
    int gridSpace = 30;

    QVBoxLayout *formBasic;
    QVBoxLayout *formLayout;
    QString backGroundColor = "#e5e5e5";
    double scaleFactor = 1;
    double lblTxtSize = 15;
    QString lblTxtColor = "#000000";
    QPoint rectPoint;
    QSize rectSize = QSize(630,907);
    qreal xRound = 40;
    qreal yRound = 40;
    QWidget *formWidget;
    QString lbl1 = "Название группы";
    QString lbl2 = "Выберите иконку";
    QLabel *nameLbl;
    QLabel *choiceLbl;
    QLineEdit *grpName;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    QStringList imgSrcLst;
    QString grpImgSrcSelected = "";
};

#endif // NEWGRPMODAL_H
