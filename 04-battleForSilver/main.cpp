#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Node
{
    explicit Node(int price) : m_price(price){}
    int m_price;
    vector<int> m_adjecents;
    unordered_set<int> m_adjecentsHashed;
};


int main() {

    int v, e;
    while(scanf("%d%d", &v,&e) == 2)
    {
        vector<Node> graph;
        std::vector<unordered_set<int> > cherryTreeHashed((unsigned)v);

        /// nacti hodnoty uzlu
        for (int i = 0; i < v; ++i)
        {
            int value;
            scanf("%d", &value);
            graph.emplace_back(Node(value));
        }

        int  maximalValue = 0;

        /// scan edges
        for (int j = 0; j < e; ++j)
        {
            int u, b;
            scanf("%d%d", &u,&b);
            graph[u-1].m_adjecents.push_back(b-1);
            graph[b-1].m_adjecents.push_back(u-1);
            graph[u-1].m_adjecentsHashed.insert(b-1);
            graph[b-1].m_adjecentsHashed.insert(u-1);

            cherryTreeHashed[u-1].insert(b-1);
            cherryTreeHashed[b-1].insert(u-1);

            int x = u-1;
            int y = b-1;

            maximalValue =  graph[x].m_price + graph[y].m_price > maximalValue ? graph[x].m_price + graph[y].m_price : maximalValue;

            /// triangle if X, a ^ Y, a => triangle exist bro
            for (auto a : graph[x].m_adjecents)
            {
                /// nasel jsem triangle
                if (cherryTreeHashed[y].count(a))
                {
                    int found = *cherryTreeHashed[y].find(a);
                    /// prebij trojici
                    int newprice = graph[a].m_price + graph[y].m_price + graph[x].m_price;
                    maximalValue =  newprice > maximalValue ? newprice : maximalValue;


                    /// najdi ctverici
                    for(auto & doCtver : graph)
                    {
                        if(doCtver.m_adjecentsHashed.count(a)  &&  doCtver.m_adjecentsHashed.count(y) && doCtver.m_adjecentsHashed.count(x) )
                        {
                            int newprice2 = graph[a].m_price + graph[y].m_price + graph[x].m_price + doCtver.m_price;
                            maximalValue =  newprice2 > maximalValue ? newprice2 : maximalValue;
                        }
                    }
                }
            }
        }

        /// count triangkle
        printf("%d\n", maximalValue );
    }
    return 0;
}









/**
 *


int main() {
    unsigned v, e;
    scanf("%d%d", &v, &e);
    std::vector<std::pair<uint64_t, std::vector<int>>> cherryTree(v);
    std::vector<unordered_set<int> > cherryTreeHashed(v);

    ///scan graph and do some epic shit
    for (int i = 0; i < e; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);

        cherryTree[x].second.push_back(y);
        cherryTree[y].second.push_back(x);
        cherryTreeHashed[x].insert(y);
        cherryTreeHashed[y].insert(x);

        /// triangle if X, a ^ Y, a => triangle exist bro
        for (auto a : cherryTree[x].second)
        {
            if (cherryTreeHashed[y].count(a))
            {
                int found = *cherryTreeHashed[y].find(a);
                cherryTree[a].first++;
                cherryTree[y].first++;
                cherryTree[found].first++;
            }
        }

    }
    ///count cherries; comprehend that all triangles are allready counted
    uint64_t numOfCherries = 0;
    for (auto &i : cherryTree)
        numOfCherries += i.second.size() >= 2 ? ((i.second.size() * (i.second.size() - 1)) >> 1) - i.first : 0;
    cout << numOfCherries << endl;
    return 0;
}


 /// ************************** COUNT TRIANGLES BFS *********************************
map<unsigned , vector<unsigned int> >  cherryGraph;

int  countTrianglesBFS(vector<Node> & graph)
{
    int  maximalValue = 0;

    /// loop graph nodes
    for( auto &currentNode : graph)
    {
        // dvojicka
        if( currentNode.m_adjecents.size() < 2)
        {
            int newprice = currentNode.m_price + graph[currentNode.m_adjecents.front()].m_price;
            maximalValue =  newprice > maximalValue ? newprice : maximalValue;
            continue;
        }

        /// potencialni trojicka

        ///save all adjecent nodes from currentNode
        unordered_set<int> openedNodes(currentNode.second.begin(), currentNode.second.end());

        ///loop adjecent nodes
        for( auto adjecent : currentNode.second)
        {
            for(auto expandedOfAdjecent : cherryGraph.find(adjecent)->second )
                if(openedNodes.find(expandedOfAdjecent) != openedNodes.end())
                    triangleCount++;

            /// finally remove expanded node from hashset
            openedNodes.erase(adjecent);
        }
    }

    return maximalValue;
}





 *
 */

