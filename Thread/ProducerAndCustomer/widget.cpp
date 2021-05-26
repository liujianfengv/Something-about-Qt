#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "Controller.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<"main thread: "<<QThread::currentThreadId();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    cotroller.begin();
}

