// C++ code to demonstrate the use of defaulted and deleted functions
#include <iostream>
using namespace std;
class A {
public:
    // A user-defined
    // parameterized cons
    A(int x) {
        cout << "This is a parameterized constructor";
    }

    // Using the default specifier to instruct the compiler to create the default
    // implementation of the constructor
    A() = default;
};

class B {
public:
    B(int x):m(x) {

    }

    // Delete the copy constructor
    B(const B&) = delete;

    // Delete the copy assignment operator
    B& operator=(const B&) = delete;
    int m;
};

int main()
{
    // executes using defaulted constructor
    A a;

    // uses parameterized constructor
    A x(1);

    B b1(1), b2(2);

//  B b3(b2);
//  b1 = b2;
    return 0;
}
