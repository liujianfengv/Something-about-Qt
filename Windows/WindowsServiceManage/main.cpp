#include <iostream>
#include "WindowsServiceManage.h"
int main()
{
    qDebug()<<WindowsServiceManage::isExist("Apple Mobile Device Service");
    WindowsServiceManage::startService("Apple Mobile Device Service");
    return 0;
}
