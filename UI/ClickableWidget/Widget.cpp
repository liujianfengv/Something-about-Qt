#include "Widget.h"
#include "ui_Widget.h"
#include <QMouseEvent>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->clickableArea->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease && watched == ui->clickableArea)
    {
        QMouseEvent* pKeyEvt = (QMouseEvent*)event;
        if (pKeyEvt->button() == Qt::LeftButton) {
            qDebug()<<pKeyEvt->button()<<"Released";
        }
    }
    return QWidget::eventFilter(watched,event);
}

