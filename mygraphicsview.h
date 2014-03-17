#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <utility>
#include "socketcomm.h"
#include "mygraphicsscene.h"
#include "frame.h"
#include "xmldataparser.h"
using namespace std;
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

signals:
    void mouseClickEvent();

public slots:
    void clickHandler();
    void ShowNextFrame();
    void DrawRect();
    /*DrawEllipse to be removed*/
    void DrawEllipse();
    /*DrawAll to be removed*/
    void DrawAll();
    void ToggleDrawRect();

public:
    explicit MyGraphicsView(QWidget *parent = 0);
    vector< pair<QRect, QString> > getRects();
    vector< pair<QRect, QString> > getEllipses();
    void setRect(bool);
    void setEllipse(bool);
    void setParser(XMLDataParser* );
    XMLDataParser* getParser();

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *event);
private:
    QRect toRect(QMap<QString,QString>);
    bool bMousePress;
    bool bGroupRect;
    bool bGroupEllipse;
    bool bDrawRect;
    QPixmap *background;
    Frame* curFrame;
    QPoint m_lastPos;
    float xRatio, yRatio;
    vector< pair<QRect, QString> > rects;
    vector< pair<QRect, QString> > ellipses;
    vector<QMap < QString,QString> > items;
    vector<QPixmap*> backgrounds;
    vector<QPixmap*>::iterator itrBackgrounds;
    QTcpSocket * socket;
    SocketComm* client;
    XMLDataParser* parser;
    QMap<int, Frame*> framedata;
    QMap<int, Frame*>::iterator itrFramedata;

};

#endif // MYGRAPHICSVIEW_H
