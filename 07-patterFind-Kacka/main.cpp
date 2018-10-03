#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>

using namespace std;


enum stat {FALSE, TRUE, VICTORY};


int g_strLen = 0;

struct State
{
    State(){};
    explicit State(int pos, char * paterPos)  : m_position(pos) , m_patternPos(++paterPos), m_cntMatches(1){}
    char * m_patternPos;
    int m_cntMatches;
    int m_position;

    int put(char  c)
    {
        if(*m_patternPos != c)
            return -1;

        m_patternPos++;

        if(++m_cntMatches == g_strLen)
            return  m_position;

        return -2;
    }

    bool operator==(const State &rhs) const {
        return m_position == rhs.m_position;
    }

    bool operator!=(const State &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const State &rhs) const {
        return m_position < rhs.m_position;
    }
};


int main()
{
    int testCasCnt;

    scanf("%d\n", &testCasCnt);
    for (int i = 0; i < testCasCnt; ++i)
    {
        string text, pattern;
        cin >> text >> pattern;

        g_strLen = (int)pattern.size();

        int cntVyskytu = 0;
        vector<int> positions;

        map<int,State> myStates;

        for (int j = 0; j < text.size(); ++j)
        {
            for(auto it = myStates.begin() ; it != myStates.end() ; )
            {

                int res = it->second.put( text[j] );
                if (res == -1) {
                    it = myStates.erase(it);
                } else if (res >= 0)
                {
                    cntVyskytu++;
                    positions.push_back(res);
                    it = myStates.erase(it);
                }

                else
                {
                    ++ it;
                }

            }

            if(text.size() - j >= pattern.size() && text[j] == pattern[0] )
            {
                myStates[j] = State(j, const_cast<char*>(pattern.c_str())) ;
            }

        }

        if(cntVyskytu == 0)
            cout << "Not Found\n";

        else
        {
            cout << cntVyskytu << endl;
            for(int i = 0 ; i < positions.size() ; ++i)
            {
                printf("%d",positions[i] +1) ;
                if(i + 1 < positions.size())
                    printf(" ");
            }
            cout << endl;
        }


        if(i+1 < testCasCnt)
            cout << endl;
    }

}