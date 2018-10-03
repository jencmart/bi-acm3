#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>
#include <unordered_map>

using namespace std;

unsigned scanInt() {int  i;scanf("%d", &i);return (unsigned)i;}
int  countTrianglesBFS();

map<unsigned , vector<unsigned int> >  cherryGraph;

int main() {
    unsigned verticesNumber = scanInt();
    unsigned edgesNumber = scanInt();

    ///scan graph
    for(int  i = 0; i < edgesNumber ; ++i)
    {
        unsigned from = scanInt();
        unsigned to = scanInt();
        cherryGraph[from].push_back(to);
        cherryGraph[to].push_back(from);
    }

    /// sum all combination numbers O(V)
    int  cherryCount = 0;
    for(auto &vertex : cherryGraph)
    {
        int  s = vertex.second.size();
        cherryCount +=  s > 1 ? s*(s-1)/2 : 0;
    }

    /// print  it
    int  trianglesNumber = countTrianglesBFS(); //countTriangles(verticesNumber);

    cout << cherryCount - trianglesNumber << endl ;
    return 0;
}

/// ************************** COUNT TRIANGLES BFS *********************************
int  countTrianglesBFS()
{
    int  triangleCount = 0;

    /// loop graph nodes
    for( auto &currentNode : cherryGraph)
    {
        if( currentNode.second.size() < 2)
            continue;

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

    return triangleCount;
}