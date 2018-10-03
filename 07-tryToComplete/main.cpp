#include <iostream>
#include <vector>

using namespace std;

struct NotFound
{

};
class Trie
{
private:
    struct Node
    {
        Node() :  m_end(false), m_maxCntOccursOfWord(0), m_index(0), m_cntEndHere(0), m_childs(26, nullptr) {}
        bool m_end;
        int  m_maxCntOccursOfWord;
        int m_cntEndHere;
        int m_index;
        vector<Node*> m_childs;
    };

public:
    Node * m_root;

    Trie() : m_root(nullptr)
    {
        m_root = new Node();
    }
    
    struct data
    {
        data( int cnt) :  m_cnt(cnt)  {}
        int m_cnt;
    };


    data insertTRIE(const char * str, Node * curr )
    {
        if(*str == '\0')
        {
            curr->m_end = true;
            curr->m_maxCntOccursOfWord;
            curr->m_cntEndHere++;
            if(curr->m_cntEndHere > curr->m_maxCntOccursOfWord)
                curr->m_maxCntOccursOfWord = curr->m_cntEndHere;

            return data(curr->m_maxCntOccursOfWord);
        }


        if(curr->m_childs[*str - 'a'] == nullptr)
            curr->m_childs[*str - 'a'] = new Node();


        data dat = insertTRIE(str+1, curr->m_childs[*str - 'a']);


        if(dat.m_cnt > curr->m_maxCntOccursOfWord)
        {
            curr->m_maxCntOccursOfWord = dat.m_cnt;
            curr->m_index = * str - 'a' ; //dat.m_idx;
        }


        return data(curr->m_maxCntOccursOfWord);
    }


    void insert(string & s) { insertTRIE(s.c_str(), m_root); }

    string findShortest(Node * curr, int occurs)
    {

        string cashed;
        char c;

        while(true)
        {

            if(curr->m_end && curr->m_cntEndHere == occurs)
                return cashed;
            c = static_cast<char>(curr->m_index + 'a');
            cashed += c;

            curr = curr->m_childs[curr->m_index];
        }

    }

    pair<int, string> find(string & s)
    {
        Node * curr = m_root->m_childs[s[0] - 'a'];

        int num;

        if(curr == nullptr)
            return make_pair(-1, "");

        for(int i = 1 ; i < s.size() ; ++i)
        {
            if(curr->m_childs[s[i] -'a'] == nullptr)
                return make_pair(-1, "");

            curr = curr->m_childs[s[i] -'a'];
        }

        if(curr != nullptr)
            num = curr->m_maxCntOccursOfWord;
        else
            return make_pair(-1, "");

        // ted bych idealne chtel bejt na poslednim indexu - a to jsem asi :)

        if(curr->m_end && curr->m_maxCntOccursOfWord == curr->m_cntEndHere)
            return make_pair(curr->m_maxCntOccursOfWord, s);

        string suffix = findShortest(curr, num);

        s += suffix;

        return make_pair(num, s);
    };
};
int main() {

    int numWords;

    Trie myTrie;

    scanf("%d\n", &numWords );

    for (int i = 0; i < numWords; ++i)
    {
        string s;
        getline(cin, s);
        myTrie.insert(s);
    }

    int numQueries;
    scanf("%d\n", &numQueries);
    for (int j = 0; j < numQueries; ++j)
    {
        string query;
        getline(cin, query);
        pair<int, string> res = myTrie.find(query);

        if(res.first == -1)
            cout << -1 << endl;
        else
            cout << res.second << " " << res.first << endl;
    }

    return 0;
}

/**

10
apple
banana
orange
applet
banana
oriental
orange
oriental
applet
bangalore
8
ban
bang
app
or
oriental
apple
hobbits
oranges

 **/