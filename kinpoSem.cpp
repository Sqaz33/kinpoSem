#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber n1("00000.90001000");
    cout << n1.toString() << endl;
    BigRealNumber n2("000009.000000010000000000000");
    cout << n2.toString();
    BigRealNumber n3 = n1 - n1;
    //cout << n2.toString();

    //while (n1 > BigRealNumber(0)) {
    //    n1 = n1 - BigRealNumber(1);
    //    cout << n1.toString() << endl;
    //}
    //bool i = n1 >= n2;
    //cout << i;

}