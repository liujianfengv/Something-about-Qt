#include "WindowsServiceManage.h"
SC_HANDLE schSCManager;
SC_HANDLE schService;
VOID __stdcall WindowsServiceManage::startService(const QString &serviceName)
{
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwOldCheckPoint;
    DWORD dwStartTickCount;
    DWORD dwWaitTime;
    DWORD dwBytesNeeded;

    // Get a handle to the SCM database.
    schSCManager = OpenSCManager(
                NULL,                    // local computer
                NULL,                    // servicesActive database
                SC_MANAGER_ALL_ACCESS);  // full access rights

    if (NULL == schSCManager)
    {
        qDebug()<<"OpenSCManager failed " << GetLastError();
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
                schSCManager,         // SCM database
                (const wchar_t*)serviceName.utf16(),            // name of service
                SERVICE_ALL_ACCESS);  // full access

    if (schService == NULL)
    {
        qDebug()<<"OpenService failed " << GetLastError();
        CloseServiceHandle(schSCManager);
        return;
    }

    // Check the status in case the service is not stopped.

    if (!QueryServiceStatusEx(
                schService,                     // handle to service
                SC_STATUS_PROCESS_INFO,         // information level
                (LPBYTE) &ssStatus,             // address of structure
                sizeof(SERVICE_STATUS_PROCESS), // size of structure
                &dwBytesNeeded ) )              // size needed if buffer is too small
    {
        qDebug()<<"QueryServiceStatusEx failed " << GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    // Check if the service is already running. It would be possible
    // to stop the service here, but for simplicity this example just returns.

    if(ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
    {
        qDebug()<<"Cannot start the service because it is already running";
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    // Save the tick count and initial checkpoint.

    dwStartTickCount = GetTickCount();
    dwOldCheckPoint = ssStatus.dwCheckPoint;

    // Wait for the service to stop before attempting to start it.

    while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
    {
        // Do not wait longer than the wait hint. A good interval is
        // one-tenth of the wait hint but not less than 1 second
        // and not more than 10 seconds.

        dwWaitTime = ssStatus.dwWaitHint / 10;

        if( dwWaitTime < 1000 )
            dwWaitTime = 1000;
        else if ( dwWaitTime > 10000 )
            dwWaitTime = 10000;

        Sleep( dwWaitTime );

        // Check the status until the service is no longer stop pending.

        if (!QueryServiceStatusEx(
                    schService,                     // handle to service
                    SC_STATUS_PROCESS_INFO,         // information level
                    (LPBYTE) &ssStatus,             // address of structure
                    sizeof(SERVICE_STATUS_PROCESS), // size of structure
                    &dwBytesNeeded ) )              // size needed if buffer is too small
        {
            qDebug()<<"QueryServiceStatusEx failed " << GetLastError();
            CloseServiceHandle(schService);
            CloseServiceHandle(schSCManager);
            return;
        }

        if ( ssStatus.dwCheckPoint > dwOldCheckPoint )
        {
            // Continue to wait and check.

            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if(GetTickCount()-dwStartTickCount > ssStatus.dwWaitHint)
            {
                qDebug() << "Timeout waiting for service to stop ";
                CloseServiceHandle(schService);
                CloseServiceHandle(schSCManager);
                return;
            }
        }
    }

    // Attempt to start the service.

    if (!StartService(
                schService,  // handle to service
                0,           // number of arguments
                NULL) )      // no arguments
    {
        qDebug() << "StartService failed" << GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }
    else qDebug() << "Service start pending...";

    // Check the status until the service is no longer start pending.

    if (!QueryServiceStatusEx(
                schService,                     // handle to service
                SC_STATUS_PROCESS_INFO,         // info level
                (LPBYTE) &ssStatus,             // address of structure
                sizeof(SERVICE_STATUS_PROCESS), // size of structure
                &dwBytesNeeded ) )              // if buffer too small
    {
        qDebug()<<"QueryServiceStatusEx failed" << GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return;
    }

    // Save the tick count and initial checkpoint.

    dwStartTickCount = GetTickCount();
    dwOldCheckPoint = ssStatus.dwCheckPoint;

    while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
    {
        // Do not wait longer than the wait hint. A good interval is
        // one-tenth the wait hint, but no less than 1 second and no
        // more than 10 seconds.

        dwWaitTime = ssStatus.dwWaitHint / 10;

        if( dwWaitTime < 1000 )
            dwWaitTime = 1000;
        else if ( dwWaitTime > 10000 )
            dwWaitTime = 10000;

        Sleep( dwWaitTime );

        // Check the status again.

        if (!QueryServiceStatusEx(
                    schService,             // handle to service
                    SC_STATUS_PROCESS_INFO, // info level
                    (LPBYTE) &ssStatus,             // address of structure
                    sizeof(SERVICE_STATUS_PROCESS), // size of structure
                    &dwBytesNeeded ) )              // if buffer too small
        {
            qDebug()<<"QueryServiceStatusEx failed " << GetLastError();
            break;
        }

        if ( ssStatus.dwCheckPoint > dwOldCheckPoint )
        {
            // Continue to wait and check.

            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if(GetTickCount()-dwStartTickCount > ssStatus.dwWaitHint)
            {
                // No progress made within the wait hint.
                break;
            }
        }
    }

    // Determine whether the service is running.

    if (ssStatus.dwCurrentState == SERVICE_RUNNING)
    {
        qDebug()<<"Service started successfully.\n";
    }
    else
    {
        qDebug()<<"Service not started.";
        qDebug()<<"  Current State: " << ssStatus.dwCurrentState;
        qDebug()<<"  Exit Code: " << ssStatus.dwWin32ExitCode;
        qDebug()<<"  Check Point: " << ssStatus.dwCheckPoint;
        qDebug()<<"  Wait Hint: " << ssStatus.dwWaitHint;
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

bool WindowsServiceManage::isExist(const QString &serviceName)
{
    schSCManager = OpenSCManager(
                NULL,                    // local computer
                NULL,                    // servicesActive database
                GENERIC_READ);

    if (NULL == schSCManager) {
        qDebug()<<"OpenSCManager failed " << GetLastError();
        return false;
    }

    // Get a handle to the service.
    schService = OpenService(
                schSCManager,         // SCM database
                (const wchar_t*)serviceName.utf16(),            // name of service
                GENERIC_READ);

    if (schService == NULL) {
        qDebug()<<"OpenService failed " << GetLastError();
        CloseServiceHandle(schSCManager);
        return false;
    } else {
        if (schService != NULL) {
           CloseServiceHandle(schService);
        }

        if (schSCManager != NULL) {
           CloseServiceHandle(schSCManager);
        }

    }
}
