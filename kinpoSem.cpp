#include <iostream>
#include "BigRealNumber.h"

int main() {
    //BigRealNumber s("3434433233.0");
    BigRealNumber s("10000.0");

    BigRealNumber d("0.0000000003");
    BigRealNumber R{};
    BigRealNumber Q{};
    s.div(d, R);
    cout << R.toString() << '\n';
}
