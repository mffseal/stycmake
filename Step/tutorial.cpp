#include <iostream>
#include <string>
#include <cmath>
#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    std::cout << std::stod("123") << std::endl;
    std::cout << "Version: " << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << std::endl;

    const double inputValue = std::stod("10");
#ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif

    std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;

    return 0;
}


