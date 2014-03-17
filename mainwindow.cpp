#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "start";


    QPushButton *GroupOne = new QPushButton(tr("DrawRect"), this);
    QPushButton *GroupTwo = new QPushButton(tr("stop"), this);
    QPushButton *GroupThree = new QPushButton(tr("start"), this);
    ui->setupUi(this);
    ui->bottom_Hlayout->addWidget(GroupOne);
    ui->bottom_Hlayout->addWidget(GroupTwo);
    ui->bottom_Hlayout->addWidget(GroupThree);

    canvas = new MyGraphicsView();

    scene = new MyGraphicsScene();
    canvas->setScene(scene);

    xmlparser = new XMLDataParser();
    xmlparser->loadXML("/home/tao/VIOS_static_demo/test.xml");
    xmlparser->parseXML();
    canvas->setParser(xmlparser);

    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    connect(timer, SIGNAL(timeout()), canvas, SLOT(ShowNextFrame()));
  //  item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg").scaled(this->width(),this->height()));
    scene->addPixmap(QPixmap("/home/tao/VIOS_static_demo/tbbt1.png").scaled(this->width(),this->height()));

    connect(GroupOne,SIGNAL(clicked()),canvas, SLOT(ToggleDrawRect()));
    connect(GroupTwo,SIGNAL(clicked()),timer, SLOT(stop()));
    connect(GroupThree, SIGNAL(clicked()),timer, SLOT(start()));
  //  connect(GroupThree,SIGNAL(clicked()),canvas, SLOT(DrawAll()));

    connect(canvas, SIGNAL(mouseClickEvent()), canvas, SLOT(clickHandler()));
    ui->top_Hlayout->addWidget(canvas);
//    ui->horizontalLayout->addWidget(canvas);




}


/*
void MainWindow::drawRect()
{
    canvas->setRect(true);
    canvas->setEllipse(false);
    vector<QRect> channelRect = canvas->getRects();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addRect(channelRect[0],QPen(QColor(255,0,0),6));
    scene->addRect(channelRect[1],QPen(QColor(255,0,0),6));

}

void MainWindow::drawEllipse()
{
    canvas->setEllipse(true);
    canvas->setRect(false);
    vector<QRect> channelRect = canvas->getEllipses();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addEllipse(channelRect[0],QPen(QColor(255,200,0),6));
    scene->addEllipse(channelRect[1],QPen(QColor(255,200,0),6));
}*/
MainWindow::~MainWindow()
{
    delete ui;
}
