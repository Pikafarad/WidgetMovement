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
            constexpr int squareWidth = 50;
            constexpr int squareHeight = 50;
            const int x = rg_2->bounded(0, this->width()- squareWidth);
            const int y = rg_2->bounded(0, 100);
            pb->setGeometry(x, y ,squareWidth, squareHeight);
            pb->show();
            auto tm = new QTimer(pb);
            tm->setInterval(1000/60);   // 60 Гц - частота монитора
            int speed = rg_2->bounded(1,2);
            connect(pb, &QPushButton::clicked, pb, &QPushButton::deleteLater);
            connect(tm, &QTimer::timeout,
                [pb, this, speed]{
                pb->move(pb->pos()+QPoint(0,speed * (pb->underMouse() ? 2 : 1)));
                if(pb->pos().y() >= height()-pb->height())
                {
                    QPalette Pal(palette());
                    Pal.setColor(QPalette::Background, Qt::red);
                    setAutoFillBackground(true);
                    setPalette(Pal);
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
