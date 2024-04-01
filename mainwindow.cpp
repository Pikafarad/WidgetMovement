#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    auto tm_1 = new QTimer();
    tm_1->setInterval(1000);
    connect(tm_1, &QTimer::timeout, [this]
    {
        auto tmStart = new QTimer(this);
        QRandomGenerator *rg_2 = QRandomGenerator::global();
        tmStart->setSingleShot(true);
        connect(tmStart,
            &QTimer::timeout,
            [this]{
                auto pb = new QPushButton("*", this);
                QRandomGenerator *rg = QRandomGenerator::global();
                int x = rg->bounded(0, this->width()-50);
                int y = rg->bounded(0, 100);
                pb->setGeometry(x, y ,50, 50);
                pb->show();
                auto tm = new QTimer(pb);
                tm->setInterval(30);
                int speed = rg->bounded(1,5);
                connect(tm, &QTimer::timeout,
                    [pb, this, speed]{
                    pb->move(pb->pos()+QPoint(0,speed * (pb->underMouse() ? 2 : 1)));
                    connect(pb, &QPushButton::clicked, pb, &QPushButton::deleteLater);
                    if(pb->pos().y() >= this->height()-pb->height())
                    {
                        QPalette Pal(palette());
                        Pal.setColor(QPalette::Background, Qt::red);
                        this->setAutoFillBackground(true);
                        this->setPalette(Pal);
                        this->show();
                        this->setWindowTitle("LOSS");
                        pb->deleteLater();
                    }
                });
                tm->start();
            });
            tmStart->setInterval(rg_2->bounded(100, 1000));
            tmStart->start();
    });
    tm_1->start();
}


MainWindow::~MainWindow()
{
}
