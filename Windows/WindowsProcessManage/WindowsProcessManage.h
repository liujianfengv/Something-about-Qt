#ifndef WINDOWSPROCESSMANAGE_H
#define WINDOWSPROCESSMANAGE_H
#include "qt_windows.h"
#include <QSet>
#include <QString>
class WindowsProcessManage
{
public:
    ///
    /// \brief GetProcessList Get all process name
    /// \return The process name set
    ///
    static QSet<QString> GetProcessList();
    ///
    /// \brief Is64BitWindows check if current os is 64bit windows
    /// \return
    ///
    static BOOL Is64BitWindows();
};
#endif
