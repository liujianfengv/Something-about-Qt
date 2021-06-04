#include <QCoreApplication>
#include "WindowsProcessManage.h"
#include <QDebug>
int main()
{
    auto result = WindowsProcessManage::GetProcessList();
    for (const auto &name : result) {
        qDebug()<<name;
    }
    qDebug()<<"is64bitWindows: "<<WindowsProcessManage::Is64BitWindows();
    return 0;
}
