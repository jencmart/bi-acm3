#include <iostream>
#include <cstdlib>     /* qsort */
#include <iostream>

#include <sstream>



struct SimpleNode
{
    int m_to;
    int m_val;
    SimpleNode(int to, int val) : m_to(to), m_val(val){}
};



struct Edge
{
    int m_from;
    int m_to;
    int m_len;
    int m_id;
    Edge(int from, int to, int len, int id) : m_from(from), m_to(to), m_len(len) ,m_id(id){}
};

template<class myType>
class vector {
    myType **m_first;
    int m_size;
    int m_capacity;

public:
    vector() : m_first(nullptr), m_size(0), m_capacity(1) { m_first = new myType *[m_capacity]; }

    vector(const vector &other) : m_first(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
        m_first = new myType *[m_capacity];
        for (int i = 0; i < m_size; ++i)
            (m_first[i]) = new myType(other[i]);
    }

    ~vector() {
        for (int i = 0; i < m_size; ++i)
            delete (m_first[i]);
        delete[] m_first;
    };

    myType &operator[](int n) { return *m_first[n]; }

    const myType &operator[](int n) const { return *m_first[n]; }

    int size() const { return m_size; }

    void push_back(const myType &val) {
        if (m_size == m_capacity) {
            m_capacity *= 2;
            auto **tmp = new myType *[m_capacity];
            for (int i = 0; i < m_size; ++i)
                tmp[i] = m_first[i];
            delete[] m_first;
            m_first = tmp;
        }
        (m_first[m_size++]) = new myType(val);
    }

    static int sortBy (Edge **r1, Edge **r2)
    { return (*r1)->m_len - (*r2)->m_len; }

    static int compare (const void * a, const void * b)
    {

        auto *edgeA = (Edge *)a;
        auto *edgeB = (Edge *)b;


        //   return (edgeA->m_len > edgeB->m_len) - (edgeA->m_len < edgeB->m_len);

        if(edgeA->m_len > edgeB->m_len)
            return 1;
        if(edgeA->m_len < edgeB->m_len)
            return -1;
        return 0;
    }


    void sort()
    {
        qsort (m_first, m_size, sizeof(myType*), (int (*)(const void *,const void *)) sortBy);
    }
};


int globalMax;

using namespace std;

int dfsSelect(int currPos, vector<vector<SimpleNode>>  & spannigTree, vector<bool> & opened, vector<bool> & closed);

int main()
{
    while(true)
    {

        vector<vector<SimpleNode>> spannigTree;
        for (int i = 0; i < 10000; ++i)
        {
            spannigTree.push_back(vector<SimpleNode>());
        }

        globalMax = 0;

        while(true)
        {
            std::string line;

            getline(std::cin, line );

            if( ! std::cin.good())
            {
                vector<bool> selected;
                vector<bool> opened;
                vector<bool> closed;

                for (int i = 0; i < 10000; ++i)
                {
                    closed.push_back(false);
                    opened.push_back(false);
                }

                int rootPos;
                for (int j = 0; j < spannigTree.size(); ++j)
                {
                    if(spannigTree[j].size() == 1)
                    {
                        rootPos = j;
                        break;
                    }

                }

                dfsSelect(rootPos, spannigTree,opened, closed);
                printf("%d\n", globalMax);
                exit(0);
            }


            if(line.empty())
            {
                vector<bool> selected;
                vector<bool> opened;
                vector<bool> closed;

                for (int i = 0; i < 10000; ++i)
                {
                    closed.push_back(false);
                    opened.push_back(false);
                }

                int rootPos;
                for (int j = 0; j < spannigTree.size(); ++j)
                {
                    if(spannigTree[j].size() == 1)
                    {
                        rootPos = j;
                        break;
                    }

                }

                dfsSelect(rootPos, spannigTree,opened, closed);
                printf("%d\n", globalMax);
                break;
            }


            std::stringstream ss;
            ss << line;

            int a,b,c;
            ss >> a >> b >> c;

            spannigTree[a].push_back(SimpleNode(b,c));
            spannigTree[b].push_back(SimpleNode(a,c));
        }
    }

    return 0;
}





int dfsSelect(int currPos, vector<vector<SimpleNode>>  & spannigTree, vector<bool> & opened, vector<bool> & closed)
{
    if(closed[currPos] || opened[currPos])
        return 0;

    if(spannigTree[currPos].size() == 1 && opened[spannigTree[currPos][0].m_to] == true )
    {
        closed[currPos] = true;
        return 0;
    }

    opened[currPos] = true;


    vector<int> maxVals;

    for (int i = 0; i < spannigTree[currPos].size(); ++i)
    {
        if(closed[spannigTree[currPos][i].m_to] || opened[spannigTree[currPos][i].m_to])
            continue;
        int val = dfsSelect(spannigTree[currPos][i].m_to, spannigTree, opened, closed);
        val += spannigTree[currPos][i].m_val;

        if(maxVals.size() < 2)
            maxVals.push_back(val);
        else
        {
            int mens = maxVals[1] < maxVals[0] ?  1 : 0;
            if(maxVals[mens] < val)
                maxVals[mens] = val;
        }
    }
    int tmpGlobMax;

    if(maxVals.size() == 1)
        globalMax = maxVals[0] > globalMax ?  maxVals[0] : globalMax;
    else
        globalMax =  maxVals[0] + maxVals[1] > globalMax ?  maxVals[0] + maxVals[1] : globalMax;

    closed[currPos] = true;

    tmpGlobMax = globalMax;

    if(maxVals.size() == 1)
        return maxVals[0];
    else
        return maxVals[0] > maxVals[1] ? maxVals[0] : maxVals[1];
}

