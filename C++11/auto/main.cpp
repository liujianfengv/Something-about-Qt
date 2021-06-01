#include <iostream>
#include <utility>
int main()
{
    auto a = 1 + 2;
    static_assert(std::is_same<decltype(a), int>::value);
    auto lambda = [](int x) { std::cout<<x<<std::endl; };
    lambda(2);
    return 0;
}
