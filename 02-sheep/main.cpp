#include <iostream>
#include <vector>
#include <set>

using namespace std;


void dfs(int i, int j, vector<vector<int>> &vector,  set<int> &visited);


int colG;
int rowG;


int wolfCount, sheepCount, side;
int main()
{
    unsigned row, col;
    char dummy;
    scanf("%d%d", &row, &col);

    string dummy2;
    getline(cin, dummy2);
    colG = col;
    rowG = row;

    int wolfSurvived = 0, sheepSurvived = 0;


    vector<vector<int>> graph  (row,vector<int>(col));

    set<set> border;
    set<int> visited;

    /// scan graph
    for (int i = 0; i < row; ++i)
    {
        for(int j = 0 ; j < col ; ++j)
        {
            char c;
            scanf("%c", &c);

//            cout << i << ":" << j << c << endl;

            if(c == '.')
                graph[i][j] = 0;

            else if( c == '#')
            {
                graph[i][j] = 3;
         //       cout << "#: " << i*col+j+1 << endl;
                visited.insert(i*col+j+1);
            }


            else if ( c == 'k')
                graph[i][j] = 1;

            else if( c == 'v')
            {
                graph[i][j] = 2;
            }

        }
        getline(cin, dummy2);
    }


    ///
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j)
        {
            unsigned cnt = visited.count(i*col+j+1);
            if(  cnt != 1)
            {
                wolfCount = sheepCount = 0;
                side = false;

                dfs( i,  j, graph, visited );

              //  cout << "w: " << wolfCount << " s: " << sheepCount << endl;

                if(side)
                {
                    wolfSurvived += wolfCount;
                    sheepSurvived += sheepCount;
                }

                else if( sheepCount > wolfCount)
                {
                    sheepSurvived += sheepCount;
                }
                else
                {
                    wolfSurvived += wolfCount;
                }
            }


        }
    }

    printf("%d %d", sheepSurvived, wolfSurvived);
}

void dfs(int i, int j, vector<vector<int>> &graph, set<int> &visited)
{
    if(visited.count(i*colG+j+1))
        return;

    visited.insert(i*colG+j+1);

    if(graph[i][j] == 1)
        sheepCount++;

    else if(graph[i][j] == 2)
        wolfCount++;

    if( !i || !j || i == rowG-1 || j == colG-1)
        side = true;

    if(j-1 >= 0)
    {
         dfs(i, j-1, graph, visited);
    }
    if(i-1 >= 0)
    {
        dfs(i-1, j, graph, visited);
    }
    if(j+1 < colG)
    {
        dfs(i,j+1, graph, visited);
    }
    if(i+1 < rowG)
    {
        dfs(i+1, j, graph, visited);
    }
}