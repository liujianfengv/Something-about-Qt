#ifndef WINDOWSSERVICEMANAGE_H
#define WINDOWSSERVICEMANAGE_H
#include "qt_windows.h"
#include <QDebug>
class WindowsServiceManage
{
public:
    static VOID __stdcall startService(const QString &serviceName);
    static bool __stdcall isExist(const QString &serviceName);
};

#endif // WINDOWSSERVICEMANAGE_H
