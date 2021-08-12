#include "widget.h"

#include <QApplication>
#include <windows.h>
#include <dbghelp.h>
#include <QMessageBox>

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException) {
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode, 16)), errAdr(QString::number((uint)record->ExceptionAddress, 16)), errMod;
    QMessageBox::critical(NULL, "The program crashes", "<FONT size=4><div>Sincerely apologize for the mistake<br/></div>" +
                                                QString("<div>errCode：%1</div><div>errAddr：%2</div></FONT>").arg(errCode).arg(errAdr),
                          QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    int *x = 0;
    *x = 100;
    return a.exec();
}
