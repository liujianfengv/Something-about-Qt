#include "MyString.h"
int main()
{
    MyString a;
    char temp[] = "Hello";
    MyString b{temp};
    MyString c{a};
    char temp1[] = "World";
    c = MyString{temp1};
    MyString d {MyString{temp}};
    cout<<d<<endl;
    d.pop_bk();
    cout<<d<<endl;
    d.push_bk('o');
    cout<<d<<endl;
    char arr[80];
    b.cpy(arr,3,0);
    cout<<arr<<endl;
    cout<<"b:"<<b<<" c:"<<c<<endl;
    b.swp(c);
    cout<<"b:"<<b<<" c:"<<c<<endl;
    return 0;
}
