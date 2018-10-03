#include <iostream>

int findGCD(int citatel, int jmenovatel);

int main()
{

    int a,b,c;
    while (scanf("%d%d%d", &a,&b,&c) == 3)
    {
        int citatel = b*a;
        int jmenovatel = c - b;


        int gcd = findGCD(citatel, jmenovatel);
        printf("%d/%d\n", citatel/gcd , jmenovatel/gcd );
    }

    return 0;
}

int findGCD(int a, int b)
{
    while (b != 0) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}