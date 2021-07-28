#include "widget.h"
#include "ui_widget.h"
#include <QColor>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineCircle();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lineCircle()
{
    ui->line_circle->setDarkColor(QColor(54, 54, 54));
    ui->line_circle->setLightColor(QColor(175, 175, 175));
    ui->line_circle->setArcLength(30);
    ui->line_circle->setRectHeight(20);
    ui->line_circle->setRectWidth(50);
    ui->line_circle->setLineCount(10);
    ui->line_circle->start();
}

