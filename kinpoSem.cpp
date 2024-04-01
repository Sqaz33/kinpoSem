#include <iostream>
#include "BigRealNumber.h"

int main() {
    int p;
    BigRealNumber n1("-5.0");
    BigRealNumber n2("3.0");
    BigRealNumber n3 = n1 / n2;
    cout << n3.toString();   
}