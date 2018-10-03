#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void doMagic(std::vector<pair<int, int>> & , int , int );


int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);


    /// scan prices (n)
    vector<pair<int,int>> data;
    for(int i = 0; i < n; ++i)
    {
        int c;
        scanf("%d",&c);
        data.emplace_back(c,0);
    }

    ///scan likes by A
    int a;
    scanf("%d", &a);
    for(int i = 0; i < a; ++i)
    {
        int x;
        scanf("%d", &x);
        data[x-1].second = 1;
    }

    /// scan likes by B
    int b;
    scanf("%d", &b);
    for(int i = 0; i < b; ++i)
    {
        int y;
        scanf("%d", &y);
        data[y-1].second = data[y-1].second == 0 ? 2 : 3;
    }

    /// sort vector
    std::sort(data.begin(), data.end(),[](pair<int, int> aa, pair<int, int> bb) {
        return aa.first < bb.first;
    });

    doMagic( data, m, k);
    return 0;
}

void doMagic(std::vector<pair<int, int>> & data, int size, int minLikes)
{
    std::vector<int> unlikedValues; // v druhe fazi budu doplnovat zleva

    std::vector<int> ALikedValues;  // budu odebirat vzdy z konce
    std::vector<int> BLikedValues;  // budu odebirat vzdy z konce

    uint64_t price = 0;
    int currentSize = 0;
    int ALikes = 0;
    int BLikes = 0;

    for (auto it = data.begin() ; it != data.end() ; ++it)
    {
        if(ALikes >= minLikes && BLikes >= minLikes && currentSize <= size)
        {
            for ( it ; it < data.end() ; ++it)
                unlikedValues.push_back(it->first);
            break;
        }

        /// hodnoty bez liku nechceme
        if(it->second == 0)
            unlikedValues.push_back(it->first);

            /// hodnoty s likem na A chceme
        else if(it->second == 1)
        {
            /// pokud mame na A malo liku
            if(ALikes < minLikes)
            {
                ALikedValues.push_back(it->first);
                price += it->first;
                ALikes++;
                currentSize++;
            }
                ///kdyz mame dost - nechceme
            else
                unlikedValues.push_back(it->first);
        }

            /// hodnoty s likem na B chceme
        else if(it->second == 2)
        {
            /// pokud mame na B malo like
            if(BLikes < minLikes)
            {
                BLikedValues.push_back(it->first);
                price += it->first;
                BLikes++;
                currentSize++;
            }
            ///kdyz mame dost - nechceme
            else
                unlikedValues.push_back(it->first);
        }

            /// variantu oba like CHCEME VZDY
        else
        {
            /// URCITE POKUD CHYBI LIKES
            if(ALikes < minLikes || BLikes < minLikes)
            {
                if( ALikes < minLikes && BLikes < minLikes) //tzn. chybi obema
                {
                    price += it->first;
                    ALikes++; BLikes++;
                    currentSize++;
                }
                else if ( ALikes < minLikes) //tzn. b uz ma dost
                {
                    price -= BLikedValues.back();
                    int i = BLikedValues.back();
                    unlikedValues.push_back(i);
                    BLikedValues.pop_back();

                    price += it->first;
                    ALikes++;
                }
                else if( BLikes < minLikes) //tzn. a uz ma dost
                {
                    price -= ALikedValues.back();
                    int i = ALikedValues.back();
                    unlikedValues.push_back(i);
                    ALikedValues.pop_back();

                    price += it->first;
                    BLikes++;
                }
                else
                    unlikedValues.push_back(it->first);
            }

                // TODO CHYBA; NEVIM JESTLI JSME ODREGULOVALI A ZVLAST, B ZVLAST !!!
                // EDIT. VIM PROTOZE KDYZ A I B, NEDAVAM TO VALUES...
                /// likes dost ale odregulovat a zvlast a b zvlast na a a b dohromady
            else if(currentSize > size )
            {
                price -= BLikedValues.back();
                int i = BLikedValues.back();
                unlikedValues.push_back(i);
                BLikedValues.pop_back();

                price -= ALikedValues.back();
                i = ALikedValues.back();
                unlikedValues.push_back(i);
                ALikedValues.pop_back();

                price += it->first;
                currentSize--;
            }

                /// varianta co nenastane nikdy
            else
                unlikedValues.push_back(it->first);
        }
    }

    if(currentSize > size || ALikes < minLikes || BLikes < minLikes)
    { cout << -1 << endl; return; }


    std::sort(unlikedValues.begin(), unlikedValues.end());

    for (auto it : unlikedValues)
    {
        if(currentSize == size)
            break;
        price += it;
        currentSize++;
    }

    if(currentSize < size)
    { cout << -1 << endl; return; }

    cout << price << endl;
}