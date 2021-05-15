#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qt_windows.h"
#include "windowsx.h"
#include "winuser.h"
#include "uxtheme.h"
#include "dwmapi.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    HWND hWnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hWnd, GWL_STYLE);
    style &= ~WS_OVERLAPPEDWINDOW;
    style |= WS_CAPTION;
    ::SetWindowLong(hWnd, GWL_STYLE, style);
    ::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = (MSG*)message;
    switch (msg->message) {
        case WM_NCCALCSIZE:
            return true;
        case WM_ACTIVATE:
            MARGINS margins;
            margins.cxLeftWidth = 1;
            margins.cxRightWidth = 1;
            margins.cyBottomHeight = 1;
            margins.cyTopHeight = 1;
            *result = DwmExtendFrameIntoClientArea(msg->hwnd, &margins);
            return true;
    default:
        return false;
    }
}

