#include "MyString.h"
#include <string.h>
MyString::MyString()
    : _data{ nullptr }
{
    _data = new char[1];
    _data[0] = '\0';
}

MyString::MyString(const char *data)
{
    if (data == nullptr) {
        _data = new char[1];
        _data[0] = '\0';
    } else {
      _data = new char[strlen(data) + 1];
      strcpy(_data, data);
    }
}

MyString::MyString(const MyString &string)
{
    _data = new char[strlen(string._data) + 1];
    strcpy(_data, string._data);
}

MyString::MyString(MyString &&source)
{
    _data = source._data;
    source._data = nullptr;
}

MyString::~MyString()
{
    delete[] _data;
}

void MyString::pop_bk()
{
    int length = strlen(_data);
    char *buff = new char[length];
    for (int i = 0; i < length - 1; ++i) {
        buff[i] = _data[i];
    }
    buff[length - 1] = '\0';
    *this = MyString{buff};
    delete[] buff;
}

void MyString::push_bk(char a)
{
    int length = strlen(_data);
    char* buff = new char[length + 2];
    for (int i = 0; i < length; i++) {
        buff[i] = _data[i];
    }
    buff[length] = a;
    buff[length + 1] = '\0';
    *this = MyString{buff};
    delete [] buff;
}

int MyString::get_length()
{
    return strlen(_data);
}

void MyString::cpy(char s[], int len, int pos)
{
    for (int i = 0; i < len; i++) {
        s[i] = _data[pos + i];
    }
    s[len] = '\0';
}

void MyString::swp(MyString &rhs)
{
    MyString tmp{rhs};
    rhs = *this;
    *this = tmp;
}

MyString &MyString::operator=(const MyString &rhs)
{
    if (this == &rhs)
        return *this;
    delete[] _data;
    _data = new char[strlen(rhs._data) + 1];
    strcpy(_data, rhs._data);
    return *this;
}
MyString operator+(const MyString& lhs, const MyString& rhs) {
    int length = strlen(lhs._data) + strlen(rhs._data);
    char* buff = new char[length + 1];
    strcpy(buff, lhs._data);
    strcat(buff, rhs._data);
    MyString temp{buff};
    delete[] buff;
    return temp;
}

istream& operator>>(istream &is, MyString &obj) {
    char * buff = new char[1000];
    is >> buff;
    obj = MyString{buff};
    delete[] buff;
    return is;
}

ostream& operator<<(ostream &os, const MyString& obj) {
    os << obj._data;
    return os;
}

