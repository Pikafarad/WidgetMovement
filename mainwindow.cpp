#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    auto tmStart = new QTimer(this);
    QRandomGenerator *rg_2 = QRandomGenerator::global();
    connect(tmStart,
        &QTimer::timeout,
        [this, tmStart, rg_2]{
            tmStart->setInterval(rg_2->bounded(100, 1000));
            auto pb = new QPushButton("*", this);
            QRandomGenerator *rg = QRandomGenerator::global();
            int squareWidth = 50;
            int squareHeight = 50;
            int x = rg->bounded(0, this->width()- squareWidth);
            int y = rg->bounded(0, 100);
            pb->setGeometry(x, y ,squareWidth, squareHeight);
            pb->show();
            auto tm = new QTimer(pb);
            tm->setInterval(100);
            int speed = rg->bounded(3,6);
            connect(tm, &QTimer::timeout,
                [pb, this, speed]{
                pb->move(pb->pos()+QPoint(0,speed * (pb->underMouse() ? 2 : 1)));
                connect(pb, &QPushButton::clicked, pb, &QPushButton::deleteLater);
                if(pb->pos().y() >= this->height()-pb->height())
                {
                    QPalette Pal(palette());
                    Pal.setColor(QPalette::Background, Qt::red);
                    setAutoFillBackground(true);
                    setPalette(Pal);
                    show();
                    setWindowTitle("LOSS");
                    pb->deleteLater();
                }
            });
            tm->start();
        });
        tmStart->start(rg_2->bounded(100, 1000));
}


MainWindow::~MainWindow()
{
}
