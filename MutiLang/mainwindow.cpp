#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTranslator>
#include <QDebug>
QTranslator translator;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!translator.load("debug\\zh_cn.qm")) {
        qDebug()<<"load qm file error";
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->installTranslator(&translator);
}


void MainWindow::on_pushButton_3_clicked()
{
    qApp->removeTranslator(&translator);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        return;
    }
    QWidget::changeEvent(event);
}

