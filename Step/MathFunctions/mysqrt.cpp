//
// Created by mffseal on 2022/11/5.
//
#include <iostream>

double mysqrt(double x) {
    if (x <= 0) return 0;
    double res = x;

    for (int i=0; i<10; ++i) {
        if (res<=0) res = 0.1;
        double delta = x - (res * res);
        res = res + 0.5 * delta / res;
        std::cout<< "Computing sqrt of " << x << " to be " << res << std::endl;
    }

    return res;
}