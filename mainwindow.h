#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <vector>
#include  <QWidget>
#include  <QPushButton>
#include <QTimer>
#include "mygraphicsview.h"
#include "mygraphicsscene.h"
#include "xmldataparser.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:

    MyGraphicsView *canvas;
    MyGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    vector <QRect> channelRect;
    XMLDataParser* xmlparser;
    QTimer *timer;

protected:
//    void mouseReleaseEvent(QMouseEvent *e);
//    void mousePressEvent(QMouseEvent *e);


public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();


public slots:
//    void drawRect();
//    void drawEllipse();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
