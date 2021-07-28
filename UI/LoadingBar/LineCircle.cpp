#include "LineCircle.h"
#include <QPainter>
LineCircle::LineCircle(QWidget *parent) : QWidget(parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(50);
    connect(_timer, &QTimer::timeout,this,[=](){
      if(_pointRect <= _lineCount){
        _pointRect++;
      }else{
        _pointRect = _pointRect % _lineCount;
      }
      update();
    });
}

void LineCircle::paintEvent(QPaintEvent *event)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    float degree = 360.0 / _lineCount;

    for(int i = 0;i < _lineCount; ++i){
      painter.rotate(degree);
      if(i == _pointRect - 1){
        drawRect(&painter, _darkColor);
      }else{
        drawRect(&painter, _lightColor);
      }
    }
}

void LineCircle::drawRect(QPainter *painter, QColor color)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    QRect rect(_arcLength, -_rectHeight / 2, _rectWidth, _rectHeight);
    painter->drawRoundedRect(rect, _rectHeight / 2, _rectHeight / 2);
    painter->restore();
}

int LineCircle::rectHeight() const
{
    return _rectHeight;
}

void LineCircle::setRectHeight(int newRectHeight)
{
    _rectHeight = newRectHeight;
}

void LineCircle::start()
{
    _timer->start();
}

int LineCircle::arcLength() const
{
    return _arcLength;
}

void LineCircle::setArcLength(int newArcLength)
{
    _arcLength = newArcLength;
}

int LineCircle::rectWidth() const
{
    return _rectWidth;
}

void LineCircle::setRectWidth(int newRectWidth)
{
    _rectWidth = newRectWidth;
}

const QColor &LineCircle::lightColor() const
{
    return _lightColor;
}

void LineCircle::setLightColor(const QColor &newLightColor)
{
    _lightColor = newLightColor;
}

const QColor &LineCircle::darkColor() const
{
    return _darkColor;
}

void LineCircle::setDarkColor(const QColor &newDarkColor)
{
    _darkColor = newDarkColor;
}

int LineCircle::lineCount() const
{
    return _lineCount;
}

void LineCircle::setLineCount(int newLineCount)
{
    _lineCount = newLineCount;
}
