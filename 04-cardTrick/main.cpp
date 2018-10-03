#include <iostream>
#include <vector>

using namespace std;
int main() {
    int numCards, startPos;
    while(scanf("%d%d", &numCards, &startPos))
    {
        vector<int> data;
        data.emplace_back(startPos);

        /// nacti hodnoty
        for (int i = 0; i < numCards; ++i)
        {
            int cardVal;
            scanf("%d", &cardVal);
            data.emplace_back(cardVal+data.back());
        }

        /// prvnich deset pozic
        for (int j = 0; j < 10; ++j)
        {
            /// spocitej pravdepodobnost dosazeni kazde pozice v poli

            for(int pozice : data)

            if(j+1>= startPos)
            {

            }

        }

    }

    return 0;
}