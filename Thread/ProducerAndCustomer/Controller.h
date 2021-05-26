#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QVector>
const int THREADS = 10;
const int ITEMS = 100000;
struct Shared{
    QMutex mutex;
    int buff[ITEMS];
    int nput;
    int nval;
};
class Producer : public QObject
{
    Q_OBJECT
public slots:
    void doWork();
private:
    int _itemCount = 0;
};

class Consumer : public QObject
{
    Q_OBJECT
public slots:
    void doWork();
private:
    void waitForItem(int index);
};

class Controller : public QObject {
    Q_OBJECT
public:
    Controller();
    ~Controller();
    void begin();
private:
    QVector<QThread*> _producerThreads;
    QThread _consumerThread;
signals:
    void produce();
    void consume();
};

#endif // CONTROLLER_H
