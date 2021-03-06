#include "WindowsProcessManage.h"
#include <tlhelp32.h>
#include <QDebug>
QSet<QString> WindowsProcessManage::GetProcessList()
{
    QSet<QString> result;
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        qDebug() << "CreateToolhelp32Snapshot (of processes)";
        return result;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        qDebug() << "Process32First"; // show cause of failure
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return result;
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        qDebug()<<"process name:"<<QString::fromWCharArray(pe32.szExeFile);
        result.insert(QString::fromWCharArray(pe32.szExeFile));
    } while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );
    return  result;
}

WINBOOL WindowsProcessManage::Is64BitWindows()
{
    #if defined(_WIN64)
     return TRUE;  // 64-bit programs run only on Win64
    #elif defined(_WIN32)
     // 32-bit programs run on both 32-bit and 64-bit Windows
     // so must sniff
     BOOL f64 = FALSE;
     return IsWow64Process(GetCurrentProcess(), &f64) && f64;
    #else
     return FALSE; // Win64 does not support Win16
    #endif
}
