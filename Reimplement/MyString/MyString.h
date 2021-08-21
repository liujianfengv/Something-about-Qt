#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
using namespace std;
class MyString
{
    friend ostream& operator<<(ostream& os, const MyString& obj);
    friend istream& operator>>(istream& is, MyString& obj);
    friend MyString operator+(const MyString & lhs, const MyString& rhs);
public:
    MyString();
    MyString(const char * data);
    MyString(const MyString &string);
    MyString(MyString&& source);
    ~MyString();

    void pop_bk();
    void push_bk(char a);
    int get_length();
    void cpy(char s[], int len, int pos);
    void swp(MyString& rhs);
    MyString& operator=(const MyString& rhs);
private:
    char* _data;
};
#endif // MYSTRING_H
