#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

    backgrounds.push_back(new QPixmap(":/image/tbbt1.png"));
    backgrounds.push_back(new QPixmap(":/image/tbbt2.png"));
    backgrounds.push_back(new QPixmap(":/image/tbbt3.png"));
    backgrounds.push_back(new QPixmap(":/image/tbbt4.png"));

    xRatio = (float)this->size().width() / (float)(*backgrounds.begin())->size().width();
    yRatio = (float)this->size().height() / (float)(*backgrounds.begin())->size().height();

    bGroupEllipse = false;
    bGroupRect = false;
    bDrawRect = false;
   // ellipses.push_back(QRect(684,205,80,170));
    QWidget::setMouseTracking(true);
    client = new SocketComm();
    client->connectToServer("127.0.0.1", 1234);

}
void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "pressed at  X: "<<e->pos().x()/xRatio <<"    Y:" << e->pos().y()/yRatio;
    QRect curRect;
    QGraphicsScene *scene;
    m_lastPos = e->pos();
    bMousePress = true;
    scene = this->scene();
 /*   if(bGroupRect)
    {
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addRect(rects[i].first,QPen(QColor(0,255,0),6));
            }
        }
    }
    if(bGroupEllipse)
    {
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(0,255,0),6));
            }
        }
    }
*/
    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        if(curRect.contains(m_lastPos) && bDrawRect)
        {
             scene->addRect(curRect,QPen(QColor(0,255,0),6));
        }

    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{

//    qDebug() << "release at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    qDebug() << "release at  X: "<<e->pos().x() / xRatio <<"    Y:" << e->pos().y()/yRatio;
//    qDebug() << "View Rect: "<<this->rect().x()<<"  "<<this->rect().y()<<"  "<<this->rect().height()<<" "<<this->rect().width();
//    qDebug() << "SceneRect: "<<this->scene()->sceneRect().x()<<"    "<<this->scene()->sceneRect().y()<<"    "<<this->scene()->sceneRect().height()<<"   "<<this->scene()->sceneRect().width();


    QRect curRect;
    QGraphicsScene *scene;
    if(bMousePress)
    {
        bMousePress = false;
        for(uint i = 0; i < items.size(); i++)
        {
            curRect = toRect(items[i]);
            scene = this->scene();
            if(curRect.contains((e->pos())) && bDrawRect)
            {
                scene->addRect(curRect,QPen(QColor(255,255,0),6));
            }

        }
    }
    if(m_lastPos == e->pos())
        emit mouseClickEvent();
 /*   if(bMousePress &&  bGroupRect)
    {
       // qDebug() << "click in MyGraphicsView";
        bMousePress = false;
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
            }
        }
        if(m_lastPos == e->pos())
            emit mouseClickEvent(rects);

    }
    if(bMousePress && bGroupEllipse)
    {
       // qDebug() << "click in MyGraphicsView";
        bMousePress = false;
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
            }
        }
        if(m_lastPos == e->pos() )
            emit mouseClickEvent(ellipses);

    }*/
}
void MyGraphicsView::clickHandler()
{

    QRect curRect;
    QString curStr;

    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        curStr =items[i]["name"] + "\n";

        if(curRect.contains(m_lastPos) && bDrawRect)
        {
            client->sendToServer(curStr);
            qDebug() <<"click in ROI";
        }
    }

}

void MyGraphicsView::ToggleDrawRect()
{
    bDrawRect = !bDrawRect;
    DrawRect();
}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
  //  qDebug() << "mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
    QRect curRect;
    QGraphicsScene *scene;
    if(!bMousePress)
        DrawRect();
    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        scene = this->scene();
        if(curRect.contains(e->pos()) && bDrawRect)
        {
            scene->addRect(curRect,QPen(QColor(255,255,0),6));
        }
    }

/*
    if(bGroupRect && !bMousePress)
    {

        if(!bGroupEllipse)
            DrawRect();
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in rect "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
    if(bGroupEllipse && !bMousePress)
    {
        if(!bGroupRect)
            DrawEllipse();
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in ellipse "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
    if(bGroupRect && bGroupEllipse && !bMousePress)
    {
        DrawAll();
        scene = this->scene();
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;

            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in rect "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;

            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in ellipse "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }

    }*/
}

void MyGraphicsView::resizeEvent(QResizeEvent *e)
{
    xRatio = (float)this->size().width() / (float)background->size().width();
    yRatio = (float)this->size().height() / (float)background->size().height();
    DrawRect();
}
void MyGraphicsView::setRect(bool val)
{
    bGroupRect = val;
}
void MyGraphicsView::setEllipse(bool val)
{
    bGroupEllipse = val;
}


void MyGraphicsView::ShowNextFrame()
{

    if(itrBackgrounds == backgrounds.end() || itrFramedata == framedata.end())
        return ;

    background = *itrBackgrounds;
    curFrame = *itrFramedata;
    items = curFrame->GetAll();
    QString curStr =  QString::number(itrFramedata.key());
    client->sendToServer( curStr);
    DrawRect();
    itrBackgrounds++;
    itrFramedata++;

}

void MyGraphicsView::DrawRect()
{
    QGraphicsScene *scene;

    this->setRect(true);
    this->setEllipse(false);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(background->scaled(this->width(),this->height()));
    if(bDrawRect)
    {
        QGraphicsScene *scene;

        this->setRect(true);
        this->setEllipse(false);
        scene = this->scene();

        scene->clear();
        scene->addPixmap(background->scaled(this->width(),this->height()));
        for(uint i = 0; i < items.size(); i++)
        {
            scene->addRect(toRect(items[i]),QPen(QColor(255,0,0),4));
        }
    }


}

QRect MyGraphicsView::toRect(QMap<QString, QString> item)
{
    QString x,y,width,height;
    x = item["x"];
    y = item["y"];
    width = item["width"];
    height = item["height"];
    return QRect(x.toInt()* xRatio, y.toInt()* yRatio,width.toInt()* xRatio,height.toInt() * yRatio);
}

void MyGraphicsView::setParser(XMLDataParser *a)
{
    parser = a;
    framedata = parser->GetData();
    itrBackgrounds = backgrounds.begin();
    itrFramedata = framedata.begin();
    background = *itrBackgrounds;
    curFrame = *itrFramedata;
    items = curFrame->GetAll();

}

XMLDataParser* MyGraphicsView::getParser()
{
    return parser;
}

vector< pair<QRect, QString> > MyGraphicsView::getRects()
{
    return rects;
}

vector< pair<QRect, QString> > MyGraphicsView::getEllipses()
{
    return ellipses;
}


/*DrawEllipse to be removed*/
void MyGraphicsView::DrawEllipse()
{
    QGraphicsScene *scene;

    this->setRect(false);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0; i < ellipses.size(); i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}
/*DrawAll to be removed*/
void MyGraphicsView::DrawAll()
{
    QGraphicsScene *scene;
    this->setRect(true);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0 ; i < rects.size();i++)
    {
        scene->addRect(rects[i].first,QPen(QColor(255,0,0),6));
    }
    for(uint i = 0 ; i < ellipses.size();i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}

