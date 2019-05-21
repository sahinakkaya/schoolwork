#include <functional>
#include <iostream>
#include "helper_functions.h"
using namespace std;
int sum(int a, int b) {
    cout << a + b << endl;
}
int main() {
    int i = 5;
    auto f = bind(sum, placeholders::_1, cref(i));
    auto g = bind(sum, placeholders::_1, i);
    while (i-- > 0) {
        f(10);
        g(10);
        cout << endl;
    }
    return 0;
}
