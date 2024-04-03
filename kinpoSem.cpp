#include <iostream>
#include "BigRealNumber.h"

int main() {
    //BigRealNumber s("3434433233.0");
    BigRealNumber s("2345234523452353.0");

    BigRealNumber d("3.0");
    BigRealNumber R{};
    BigRealNumber Q{};
    s.div(d, R);
    unsigned long long int i = 2345234523452353;
    i /= 3;
    cout << i << "\n";
    cout << R.toString() << '\n';
}
