#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber n("1234.9");
    BigRealNumber n1("9321.01");
    BigRealNumber n2 = n + n1;
    cout << n2.toString();

}


