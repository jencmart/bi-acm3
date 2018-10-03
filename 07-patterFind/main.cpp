#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const long prime = 33554393;
const int letters = 64;

int ascii(char c)
{
    if (c == ' ')
        return 0;
    if (islower(c))
        return c - 'a' + 1;
    else
        return c - 'A' + 27;
}

int searchWord(const char * word, const char * text, unsigned sizeWord, unsigned textSize)
{
    unsigned long i, bM_1 = 1, valueWord = 0, valueText = 0, m = sizeWord, n = textSize;


    for (i = 0; i < m; i++)
    {
        valueWord = (valueWord * letters + ascii(word[i])) % prime;
        valueText = (valueText * letters + ascii(text[i])) % prime;
    }

    for (i = 1; i < m; i++)
        bM_1 = (letters * bM_1) % prime;

    for (i = 0; valueWord != valueText; i++)
    {
        valueText = (valueText + letters * prime - ascii(text[i]) * bM_1) % prime;
        valueText = (valueText * letters + ascii(text[i + m])) % prime;
        if (i > n - m)
            return -1;
    }

    return (int)i;
}

int main()
{
    int testCasCnt;

    scanf("%d\n", &testCasCnt);
    for (int i = 0; i < testCasCnt; ++i)
    {
        string A, B;
        cin >> A >> B;

        int cntVyskytu = 0;
        vector<int> positions;

        while(true)
        {
            int position;
            if(! positions.empty())
            {
                 position = searchWord((B.c_str()), A.c_str() + positions.back() + 1, (unsigned) B.size() , (unsigned)A.size() - positions.back() - 1);
            }
            else
            {
                position = searchWord((B.c_str()), A.c_str() , (unsigned) B.size() , (unsigned)A.size() );
            }

            if(position == -1)
                break;

            cntVyskytu++;
            positions.push_back(position + 1);
        }

        if(cntVyskytu == 0)
            cout << "Not Found\n";

        else
        {
            cout << cntVyskytu << endl;
            for(int i = 0 ; i < positions.size() ; ++i)
            {
                printf("%d",positions[i] ) ;
                if(i + 1 < positions.size())
                    printf(" ");
            }
            cout << endl;
        }

    }

}