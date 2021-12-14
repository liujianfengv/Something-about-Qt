#ifndef SIGNALPROGRESSBAR_H
#define SIGNALPROGRESSBAR_H

#include <QProgressBar>
#include <QObject>

class SignalProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit SignalProgressBar(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
private:
    QVector<QRect> calcRectVec();
    void drawSignalProgress(QPainter *painter,const QVector<QRect> &rectVec);
};

#endif // SIGNALPROGRESSBAR_H
