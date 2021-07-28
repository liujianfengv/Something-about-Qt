#ifndef LINECIRCLE_H
#define LINECIRCLE_H

#include <QWidget>
#include <QColor>
#include <QTimer>
class LineCircle : public QWidget
{
    Q_OBJECT
public:
    explicit LineCircle(QWidget *parent = nullptr);
    // QWidget interface
    int lineCount() const;
    void setLineCount(int newLineCount);

    const QColor &darkColor() const;
    void setDarkColor(const QColor &newDarkColor);

    const QColor &lightColor() const;
    void setLightColor(const QColor &newLightColor);

    int rectWidth() const;
    void setRectWidth(int newRectWidth);

    int arcLength() const;
    void setArcLength(int newArcLength);

    int rectHeight() const;
    void setRectHeight(int newRectHeight);

    void start();

protected:
    void paintEvent(QPaintEvent *event);
private:
    void drawRect(QPainter* painter,QColor color);
private:
    int _lineCount;
    QColor _darkColor;
    QColor _lightColor;
    int _rectWidth;
    int _rectHeight;
    int _arcLength;
    int _pointRect;
    QTimer *_timer;
};

#endif // LINECIRCLE_H
