#include <iostream>
#include <vector>
#include <list>

using  namespace std;


void recalculate(int & numOfMov,vector<int> & banksVector)
{
    for(int i = 0 ; i < banksVector.size() ; )
    {
        if(banksVector[i] < 0)
        {
            /// do magic move
            numOfMov ++;
            int val = banksVector[i];

            banksVector[i] *= -1;
            if(i == 0)
            {
                banksVector.back() += val;
                banksVector[i+1] += val;
            }
            else if(i+1 == banksVector.size())
            {
                banksVector[i-1] += val;
                banksVector.front() += val;
            }
            else
            {
                banksVector[i-1] += val;
                banksVector[i+1] += val;
            }

            ///get new i
            i = i == 0 ? (int)banksVector.size() - 1 : i-1;

            int shift = 0;
            while(banksVector[i] >= 0)
            {
                if(shift == banksVector.size()+1)
                    return;
                i = i == 0 ? (int)banksVector.size() - 1 : i-1;
                shift++;
            }
        }

        else
        {
            i++;
        }
    }
}
int main() {
    freopen("A.in", "r", stdin);

    int banks;
    scanf("%d", &banks);

    vector<int> banksVector;

    for (int i = 0; i < banks; ++i)
    {
        int capital;
        scanf("%d", &capital);
        banksVector.push_back(capital);
    }

    /// do some math.
    int numberOfMoves = 0;

    recalculate(numberOfMoves, banksVector);

    printf("%d\n", numberOfMoves);
    return 0;
}