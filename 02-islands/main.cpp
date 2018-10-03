#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

struct Node
{
    explicit Node(int name, int m_dfsNum = -1, int m_lowNum = INT32_MAX, bool m_open = false, bool m_closed = false) : m_dfsNum(m_dfsNum), m_lowNum(m_lowNum),
                                                                   m_open(m_open), m_closed(m_closed), m_name(name) {}
    int  m_name;
    int  m_dfsNum;
    int  m_lowNum;
    bool m_open;
    bool m_closed;
    std::vector<int> adjecents;
};


int countCutEdges(vector<Node> &graph);

bool dfsCount(int & cnt, int nodeName, vector<Node> &graph, vector<pair<int, vector<int>>> &);
int bfsRecursiveTree(vector<pair<int, vector<int>>> &recursiveTree);


int main() {
    unsigned v,e;

    ///scan all graphs
    scanf("%d%d", &v, &e);
    while(v && e)
    {
        vector<Node> graph;
        for(int i = 0 ; i < v ; ++i)
        {
            graph.emplace_back(Node(i));
        }

        for(int i = 0; i < e ; ++i)
        {
            int nodeA, nodeB;
            scanf("%d%d", &nodeA, &nodeB);
            graph[nodeA-1].adjecents.emplace_back(nodeB-1);
            graph[nodeB-1].adjecents.emplace_back(nodeA-1);
        }

        ///count it and print it


        printf("%d", countCutEdges(graph));

        scanf("%d%d", &v, &e);

        cout << endl;
     //   for(auto &x : graph)
       // {
         //   cout << x.m_name << " : "<< x.m_dfsNum  <<" : " << x.m_lowNum << endl;
        //}
    }
    return 0;
}

int countCutEdges(vector<Node> &graph )
{
    int cnt = 0;
    vector<pair<int, vector<int>>> recursiveTree(graph.size());
    recursiveTree[0].first = -1;
    dfsCount(cnt, 0, graph, recursiveTree);

    int result = bfsRecursiveTree(recursiveTree);
    // cut vertices are the non-root vertices U having a child V such that low[V] >= dfs-number[U], 
    // plus the root vertex, if the root vertex has degree two or more in the dfs tree.
    // count all cutted verticies and return it

    int finalCount = 0;
    set<int> cuttedEdges;
    list<int> myQueue;
    myQueue.push_back(0);
    while(! myQueue.empty())
    {
        int current = myQueue.front();
        myQueue.pop_front();
        for(auto x : recursiveTree[current].second)
        {
            myQueue.push_back(x);
            if(graph[x].m_lowNum >= graph[current].m_dfsNum && current)
            {
                cuttedEdges.insert(current);
            }
        }
    }

    if(recursiveTree[0].second.size() >= 2)
        cuttedEdges.insert(0);

    /// pocita mi to o jedna vice :(
    return (int)cuttedEdges.size();
}

int bfsRecursiveTree(vector<pair<int, vector<int>>> &recursiveTree)
{

}

bool dfsCount(int & cnt, int nodeName, vector<Node> &graph, vector<pair<int, vector<int>>> & recursiveTree)
{
    if(graph[nodeName].m_open)
    {
        return false;
    }

    graph[nodeName].m_open = true;
    graph[nodeName].m_dfsNum = ++cnt;

    for( auto & expanded : graph[nodeName].adjecents)
    {
        if(  dfsCount(cnt,graph[expanded].m_name, graph, recursiveTree) )
        {
            // vede hrana ve stromu z graph[nodeName] -> graph[expanded]
            // aka.  graph[nodeName] . potomci += graph[expanded];
            //    graph[expanded] . parent = graph[nodeName]

            recursiveTree[nodeName].second.push_back(expanded);
            recursiveTree[expanded].first = nodeName;
        }

        int possibleLow = graph[expanded].m_closed ? graph[expanded].m_lowNum : graph[expanded].m_dfsNum;
                graph[nodeName].m_lowNum =  possibleLow < graph[nodeName].m_lowNum ? possibleLow : graph[nodeName].m_lowNum ;
    }
    graph[nodeName].m_closed = true;

    return true;
}
