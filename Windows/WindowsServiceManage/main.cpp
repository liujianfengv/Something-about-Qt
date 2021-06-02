#include <iostream>
#include "WindowsServiceManage.h"
int main()
{
    WindowsServiceManage::startService("Apple Mobile Device Service");
    return 0;
}
