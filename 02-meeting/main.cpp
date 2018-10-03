#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int colG;
int rowG;


int wolfCount, sheepCount, side;

set<int> visited;

void bfs(int first, int second, vector<vector<int>> &, set<int> & ,vector<vector<pair<int,int>>> &,  pair<int, int>,  pair<int, int>  );

int main() {
    unsigned tests;
    char dummy;

    scanf("%d", &tests);

    /// for N of testcases
    for (int testNum = 0; testNum < tests; ++testNum)
    {
        unsigned row, col;

        scanf("%d %d", &row, &col);

        row+=2;
        col+=2;
        string dummy2;

        colG = col;
        rowG = row;
        pair<int, int> A;
        pair<int, int> B;
        pair<int, int> C;

        vector<vector<int>> graph(row, vector<int>(col));

        vector<vector<pair<int,int>>> values(row, vector<pair<int,int>>(col, make_pair(0,0) ));

        set<int> walls;

        getline(cin, dummy2);
        /// SCAN GRAPH
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
            {

                if( i == 0 || j == 0  || i == row-1 || j == col-1)
                {
                    graph[i][j] = 0;
                    continue;
                }

                char c;
                scanf("%c", &c);
                if ( c == '\0')
                    scanf("%c", &c);

                if (c == '.')
                    graph[i][j] = 0;

                else if (c == '#') {
                    graph[i][j] = 1;
                    walls.insert(i * col + j + 1);

                }
                else if (c == '1')
                {
                    graph[i][j] = 0;
                    A.first = i;
                    A.second = j;
                }

                else if (c == '2')
                {
                    graph[i][j] = 0;
                    B.first = i;
                    B.second = j;
                }
                else if (c == '3')
                {
                    graph[i][j] = 0;
                    C.first = i;
                    C.second = j;
                }
            }
            if(!(i == 0 || i == row-1))
                getline(cin, dummy2);
        }

        bfs(A.first, A.second, graph, walls, values, B, C);
        bfs(B.first, B.second, graph, walls, values, A, C);
        bfs(C.first, C.second, graph, walls, values, A, B);

        int min = INT32_MAX;
        for(int i = 0; i < row ; ++i)
        {
            for(int j = 0 ; j < col ; ++j)
            {
                if ( ! walls.count(i * col + j + 1) && visited.count(i * col + j + 1) )
                {
                    if (values[i][j].first < min && values[i][j].second == 4)
                        min =  values[i][j].first;
                }

            }
        }

      /**
       *   for(auto &x : values)
        {
            for(auto y : x)
            {
                cout << y << " ";
            }

            cout << endl;
        }

       */

        printf("%d\n", min);
    }
}

void bfs(int i, int j, vector<vector<int>> & graph, set<int> & walls, vector<vector<pair<int,int>>> & values,  pair<int, int> one ,  pair<int, int> other)
{
    visited.clear();

    int cnt = 0;

    struct triplet
    {
        triplet(int i, int j, int depth) : i(i), j(j), depth(depth) {}

        int i;
        int j;
        int depth;
    };
    queue<triplet> myQueue;



    int depth = 0;

    myQueue.push(triplet(i,j,depth));
    values[i][j].second++;

    while(!myQueue.empty())
    {
        int iNew = myQueue.front().i;
        int jNew = myQueue.front().j;

        if((iNew == one.first && jNew == one.second ) || (iNew == other.first && jNew == other.second) )
            cnt++;

        if(cnt == 2)
            return;

        depth = myQueue.front().depth;
        myQueue.pop();

        visited.insert(iNew * colG + jNew + 1);
        values[iNew][jNew].second++;

         if( values[iNew][jNew].first < depth)
            values[iNew][jNew].first = depth;

        if(jNew-1 >= 0 && ! walls.count(iNew * colG + jNew ) && ! visited.count(iNew * colG + jNew ) )
        {
            myQueue.push(triplet(iNew, jNew-1, depth+1));
        }
        if(iNew-1 >= 0 && ! walls.count((iNew-1) * colG + jNew + 1) && ! visited.count((iNew-1) * colG + jNew + 1) )
        {

            myQueue.push(triplet(iNew-1, jNew,  depth+1));
        }
        if(jNew+1 < colG && ! walls.count(iNew * colG + jNew + 2) && ! visited.count(iNew * colG + jNew + 2) )
        {
            myQueue.push(triplet(iNew, jNew+1,  depth+1));
        }
        if(iNew+1 < rowG &&  ! walls.count((iNew+1) * colG + jNew + 1) && ! visited.count((iNew+1) * colG + jNew + 1) )
        {
            myQueue.push(triplet(iNew+1, jNew,depth+1));
        }
    }

}
