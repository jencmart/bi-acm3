#include <iostream>
#include <cmath>
int main()
{
    freopen("H.in", "r", stdin);
    int m, n;
    scanf("%d%d", &m,&n);

    int cnt = 0;
    for(int i =0 ; i <= m ; i++)
        for( int j = i; j <= m ; j++)
            for(int k = j; k <= m ; ++k)
                if(i*i + j*j == k*k)
                    cnt++;

    int finalCnt = 0;
    for(int f = 2 ; f <= n ; ++f)
        finalCnt += cnt;

    printf("%d\n", finalCnt);
    return 0;
}