#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

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
            if (cherryTreeHashed[y].count(a)) {
                int found = *cherryTreeHashed[y].find(a);
                cherryTree[a].first++;
                cherryTree[y].first++;
                cherryTree[found].first++;
            }
    }
    ///count cherries; comprehend that all triangles are allready counted
    uint64_t numOfCherries = 0;
    for (auto &i : cherryTree)
        numOfCherries += i.second.size() >= 2 ? ((i.second.size() * (i.second.size() - 1)) >> 1) - i.first : 0;
    cout << numOfCherries << endl;
    return 0;
}