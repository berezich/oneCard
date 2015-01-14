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
    NewGrpModal(QSize size, double scale,QStringList grpIconLst, QWidget *parent = 0);
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

    int columnsNum = 3;
    int rowsNum = 4;
    QSize iconSize = QSize(135,135)*0.98;
    QSize iconOkSize = QSize(120,60);
    QSize screenSize = QSize(720,1280);
    int gridSpace = 30;

    QVBoxLayout *formBasic;
    QVBoxLayout *formLayout;
    QString backGroundColor = "#e5e5e5";
    double scaleFactor = 1;
    double lblTxtSize = 18;
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
    QList<SimpleIcon *> iconsGrid;
    int selectedIcon=-1;
};

#endif // NEWGRPMODAL_H
