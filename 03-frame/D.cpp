#include <iostream>


void bad()
{
    printf("NO\n");
}

int main() {

    freopen("D.in", "r", stdin);
    int height, width;
    scanf("%d%d", &height, &width);

    int testCases;
    scanf("%d", &testCases);
    for (int i = 0; i < testCases; ++i)
    {
        int dlazdickaSize;
        scanf("%d", &dlazdickaSize);

        int height0 = height, height1 = height;
        int width0 = width, width1 = width;

        if(dlazdickaSize == 2)
        {
            printf("YES\n");
            continue;
        }

        int modRes1 = width % dlazdickaSize;

        if(modRes1 == 0)
        {
            height0--; height1--;
        }
        else if(modRes1 == 1)
        {
            height0--;

        }
        else if (modRes1 == 2)
        {
            // leve it
        }
        else
        {
            bad();
            continue;
        }

        int modRes2 = height0%dlazdickaSize;
        if(modRes2 == 0)
        {
            width1--;
        }
        else if (modRes2 == 1)
        {
         // do nothing
        }
        else
        {
            bad();
            continue;
        }


        int modRes3 = width1%dlazdickaSize;

        if(modRes3 == 0)
        {
            height1--;
        }
        else if( modRes3 == 1)
        {
            //do nonothing
        }
        else
        {
            bad();
            continue;
        }


        if(height1%dlazdickaSize != 0)
        {
            bad();
            continue;
        }

        printf("YES\n");
    }

    return 0;
}