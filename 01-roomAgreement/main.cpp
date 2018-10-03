#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main() {
    int numStatements;
    scanf("%d", &numStatements);



    for (long i = 0; i < numStatements; ++i)
    {
        long count;
        scanf("%ld", &count);
        std::unordered_map<long, long> sumMap;
        long cnt = 0, sum = 0;

        for (int k = 0; k < count; ++k) {
            int number;
            scanf("%d", &number);
            sum += number;
            !sum ? cnt++ : cnt;
            if(sumMap.find(sum) != sumMap.end())
            {
                cnt += sumMap.find(sum)->second;
                (sumMap.find(sum)->second)++;
            }
            else { sumMap[sum] = 1 ; }
        }
        printf("%ld\n", cnt);
    }
    return 0;
}