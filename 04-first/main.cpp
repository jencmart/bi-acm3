#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    int n;
    while(scanf("%d", &n) == 1)
    {
        struct edge
        {
            edge(int a, int b, int dist): m_a(a), m_b(b), m_dist(dist){};
            int m_a, m_b, m_dist;

            const bool operator<(const  edge  & other)
            {
              return this->m_dist < other.m_dist;
            }
        };

        vector<edge> myEdges;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if(i != j)
                {
                    int dist;
                    scanf("%d", &dist);
                    myEdges.emplace_back( edge(i,j, dist));
                }
            }
        }
        sort(myEdges.begin(), myEdges.end());

        vector<vector<int>> myGraph(n);

        for(auto e : myEdges)
        {

        }
    }
}