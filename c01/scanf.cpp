
#include <stdio.h>

bool fastInt(int *i)
{
    register int c = getchar_unlocked();
    int x;
    x = 0;
    int neg = 0;

    for( ; ((c<48 || c>57) && c != '-'); c = getchar_unlocked())
    {
        if(c == EOF)
        {
            return false;
        }
    }
    if(c=='-') {
        neg = 1;
        c = getchar_unlocked();
    }

    for(; c>47 && c<58 ; c = getchar_unlocked())
    {
        x = (x<<1) + (x<<3) + c - 48;
    }

    if(neg)
        x = -x;
    *i = x;
    return true;
}

int main()
{
    int i;
    while(scanf("%d", &i) != EOF)
    {
//     printf("%d\n", i);
    }

    return 0;
}
