#include <cstdlib>
#include <ctime>
#include "../MathLib/math_lib.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    MathTest test(5, 1, 20);
    test.run();

    return 0;
}