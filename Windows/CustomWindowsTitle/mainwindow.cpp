#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <QDebug>

// All predefined window menu items have identifier numbers greater than 0xF000.
// If an application adds commands to the window menu, it should use identifier numbers less than 0xF000.
#define MENU_ITEM_TEST 0x0100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMenuTestClicked()
{
    qDebug()<<"Test Menu Clicked!";
}

void MainWindow::initMenu()
{
    HWND hWnd = (HWND)this->winId();
    HMENU menu = GetSystemMenu(hWnd, false);
    AppendMenuA(menu, MF_STRING, MENU_ITEM_TEST, "Test");
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = (MSG*)message;
    switch (msg->message) {
    case WM_SYSCOMMAND:
        {
            if (MENU_ITEM_TEST == msg->wParam) {
                onMenuTestClicked();
            }
        }
        break;
    default:
        break;
    }

    //If you return false, this native event is passed back to Qt,
    //which translates the event into a Qt event and sends it to the widget

    return false;
}

