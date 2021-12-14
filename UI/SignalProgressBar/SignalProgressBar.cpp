#include "SignalProgressBar.h"

#include <QPainter>

SignalProgressBar::SignalProgressBar(QWidget *parent):
    QProgressBar(parent)
{

}

void SignalProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    drawSignalProgress(&painter, calcRectVec());
}

QVector<QRect> SignalProgressBar::calcRectVec()
{
    QVector<QRect> res;
    const qreal widthInterval = width() / 9;
    const qreal heightInterval = height() / 8;
    for (int i = 0; i < 5; ++i) {
        res << QRect(widthInterval * (2 * i),
                     height() / 2 - (heightInterval * i),
                     widthInterval,
                     height() / 2 + (heightInterval * i));
    }
    return res;
}

void SignalProgressBar::drawSignalProgress(QPainter *painter, const QVector<QRect> &rectVec)
{
    int progressValue = value();
    if (progressValue == 0) {
        return ;
    } else if (progressValue == 100) {
        for (const auto &rect : rectVec) {
            painter->drawRect(rect);
        }
        return ;
    } else {
        for (int i = 0; i <= (value() / 20); ++i) {
            painter->drawRect(rectVec[i]);
        }
        return ;
    }
}
