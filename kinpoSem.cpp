#include <iostream>
#include "BigRealNumber.h"

int main() {
    BigRealNumber s("34.434534534");
    BigRealNumber t("119.0");
    BigRealNumber v{};
    s.mul(t, v);
    cout << v.toString();
}
