#include <iostream>
#include "BigRealNumber.h"

int main() {
    //BigRealNumber s("3434433233.0");
    BigRealNumber s("10000.0");

    BigRealNumber d("0.0000000002342343");
    BigRealNumber r = s / s;
    cout << r.toString() << '\n';
}
