#include "Controller.h"
#include <QThread>
#include <QDebug>
int items = 0;
Shared shared;
void Producer::doWork()
{
    while (1) {
        shared.mutex.lock();
        if (shared.nput >= ITEMS) {
            shared.mutex.unlock();
            qDebug()<<"thread id: "<<QThread::currentThreadId()<<" produce["<<_itemCount<<"]items";
            return;
        }
        shared.buff[shared.nput] = shared.nval;
        qDebug()<<"thread id: "<<QThread::currentThreadId()<<" produce items["<<shared.nput<<"]";
        shared.nput++;
        shared.nval++;
        _itemCount++;
        shared.mutex.unlock();
    }
}

void Consumer::doWork()
{
    bool error = false;
    for (int i = 0; i < ITEMS; i++) {
        waitForItem(i);
        if (shared.buff[i] != i) {
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

void Consumer::waitForItem(int index)
{
    for (;;) {
        shared.mutex.lock();
        if (index < shared.nput) {
            shared.mutex.unlock();
            return;
        }
        shared.mutex.unlock();
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
