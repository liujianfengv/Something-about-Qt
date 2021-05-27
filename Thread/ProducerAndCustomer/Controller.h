#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QVector>
#include <QWaitCondition>
const int THREADS = 10;
const int ITEMS = 100000;
struct {
    QMutex mutex;
    int nput;
    int nval;
} put;

struct {
    QMutex mutex;
    QWaitCondition cond;
    int nready;
} nready;

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
