#include <iostream>
#include "BigRealNumber.h"

int main() {
    int p;
    BigRealNumber n1("1.0");
    BigRealNumber n2("0.00004");
    BigRealNumber n3 = n1 / n2;
    cout << n3.toString();   
}