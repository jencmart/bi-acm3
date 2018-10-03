
#include <iostream>
#include <vector>
#include <algorithm>

void insertVal(int val);
void printOccur(int val2, int from, int to);
void deleteLast();

std::vector<std::vector<int>> array2d(200000);
std::vector<int> array1d;

int main() {
    int numStatements;
    scanf("%d", &numStatements);

    for(int i = 0 ; i < numStatements ; ++i)
    {
        int op;
        scanf("%d", &op);
        switch (op)
        {
            case 1 :
                int val;
                scanf("%d", &val);
                insertVal(val);
                break;
            case 2 :
                int val2, from, to;
                scanf("%d%d%d", &val2, &from, &to);
                printOccur(val2, from, to);
                break;
            default :
                deleteLast();
                break;
        }
    }

    return 0;
}

void deleteLast()
{
    if(array1d.empty())
    {
        printf("%s", "invalid\n");
    }
    else
    {
        int val = array1d.back();
        array1d.pop_back();
        array2d[val].pop_back();
    }
}

void printOccur(int val, int from, int to)
{
    std::vector<int>::iterator itFrom = std::lower_bound(array2d[val].begin(),array2d[val].end(),from);
    std::vector<int>::iterator itTo = std::upper_bound(array2d[val].begin(),array2d[val].end(),to);
    int numOccurences = itTo - itFrom;

    printf("%d\n", numOccurences);
}

void insertVal(int val)
{
    //vlozim na opravdovou pozici
    array1d.push_back(val);
    // vkladam pozici pocitanou od 1
    array2d[val].push_back((int)array1d.size());
}

