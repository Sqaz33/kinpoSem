#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber s("1.2");
    BigRealNumber d("3.0");
    BigRealNumber R{};
    BigRealNumber Q{};
    s.div(d, R);
    cout << R.toString() << '\n';
}
