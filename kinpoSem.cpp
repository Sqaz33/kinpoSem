#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber s("12.0");
    s.shiftNumber(1, true);
    cout << s.toString();
}