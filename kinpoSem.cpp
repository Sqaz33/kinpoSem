#include <iostream>
#include "BigRealNumber.h"

int main() {
    int p;
    //BigRealNumber n1("10000.0");
    //BigRealNumber n2("0.000100000");
    //cout << n1.toString() << endl;
    //cout << n2.toString() << endl;
    //BigRealNumber n3(0);
    //while (n1 > BigRealNumber(0)) {
    //    n1 = n1 - BigRealNumber(1);
    //    cout << n1.toString() << endl;
    //    if (n1 == n3) {
    //        cin >> p;
    //    }
    //}
    //bool i = n1 >= n2;
    //cout << i;

    BigRealNumber n1("0.000000000000000000000000000000000001");
    BigRealNumber n2("0.001001");
    bool b = n1 > n2;

    cout << b;
    
    

}