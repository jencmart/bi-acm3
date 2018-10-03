#include <iostream>
#include <cinttypes>

using namespace std;

int main() {
    int numStatements;
    scanf("%d", &numStatements);

    for (int i = 0; i < numStatements; ++i)
    {
        /// scan it
        unsigned long long y;
        scanf("%lld", &y);
        __uint128_t x = y;

        ///count it
        __uint128_t result = (x*x*x + 3*x*x + 2*x)/2;

        ///print it
        auto upper = (uint64_t) result;
        auto lower = (uint64_t) (result >> 64 );
        if(lower)
        {
            std::cout << lower;
        }
        std::cout << upper << std::endl;
    }
    return 0;
}