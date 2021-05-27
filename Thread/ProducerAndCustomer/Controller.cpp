#include "Controller.h"
#include <QThread>
#include <QDebug>
int items = 0;
int buff[ITEMS];
void Producer::doWork()
{
    while (1) {
        put.mutex.lock();
        if (put.nput >= ITEMS) {
            put.mutex.unlock();
            qDebug()<<"thread id: "<<QThread::currentThreadId()<<" produce["<<_itemCount<<"]items";
            return;
        }
        buff[put.nput] = put.nval;
        qDebug()<<"thread id: "<<QThread::currentThreadId()<<" produce items["<<put.nput<<"]";
        put.nput++;
        put.nval++;
        _itemCount++;
        put.mutex.unlock();

        bool doSignal = false;
        nready.mutex.lock();
        doSignal = (nready.nready == 0);
        nready.nready++;
        nready.mutex.unlock();
        if (doSignal) {
            nready.cond.wakeAll();
        }
    }
}

void Consumer::doWork()
{
    bool error = false;
    for (int i = 0; i < ITEMS; i++) {
        nready.mutex.lock();
        while (nready.nready == 0) {
            nready.cond.wait(&nready.mutex);
        }
        nready.nready--;
        nready.mutex.unlock();
        if (buff[i] != i) {
            error = true;
        } else {
            qDebug()<<QString("consume item[%1]").arg(i);
        }
    }
    if (error) {
        qDebug()<<"Error occur in consume";
    }  else {
        qDebug()<<"Success!";
    }
}

Controller::Controller():
    _producerThreads(THREADS, nullptr)
{
    for (auto &th : _producerThreads) {
        th = new QThread;
    }
}

Controller::~Controller()
{
    _consumerThread.quit();
    _consumerThread.wait();
}

void Controller::begin()
{
    for (auto & th : _producerThreads) {
        Producer *worker = new Producer;
        worker->moveToThread(th);
        connect(th, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::produce, worker, &Producer::doWork);
        th->start();
    }
    Consumer *consumer = new Consumer;
    consumer->moveToThread(&_consumerThread);
    connect(&_consumerThread, &QThread::finished, consumer, &QObject::deleteLater);
    connect(this, &Controller::consume, consumer, &Consumer::doWork);
    _consumerThread.start();

    emit produce();
    emit consume();
}
