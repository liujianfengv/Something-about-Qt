#include <iostream>
#include <type_traits>

struct A {double x;};
const A* a;

decltype (a->x) y;
decltype ((a->x)) z = y;

template <typename T, typename U>
auto add(T t, U u)->decltype (t + u) {
    return t + u;
}

int main()
{
    int i = 33;
    decltype (i) j = i * 2;
    std::cout << "i and j are the same type?" << std::boolalpha
              << std::is_same<decltype (i), decltype (j)>::value<<'\n';

    auto f = [](int a, int b) ->int {
        return a * b;
    };
    decltype (f) g = f;
    i = f(2, 2);
    j = g(3, 3);
    std::cout << "i = " << i << ","
              << "j = " << j << '\n';
    return 0;
}
