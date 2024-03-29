#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber n("0.90001");
    BigRealNumber n1("0.00000001");
    BigRealNumber n2 = n1 - n;
    cout << n2.toString();

}