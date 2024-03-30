#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber n1("00000.90001000");
    BigRealNumber n2("00000.00000001");
    BigRealNumber n3 = n1 - n1;
    //cout << n2.toString();

    //while (n1 > BigRealNumber(0)) {
    //    n1 = n1 - BigRealNumber(1);
    //    cout << n1.toString() << endl;
    //}
    bool i = n1 >= n2;
    cout << i;

}