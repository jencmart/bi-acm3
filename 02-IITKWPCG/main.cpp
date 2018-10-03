#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    unsigned m_nodeA;
    unsigned m_nodeB;
    unsigned m_weight;

    Edge(unsigned nodeA, unsigned nodeB, unsigned weight) : m_nodeA(nodeA), m_nodeB(nodeB), m_weight(weight) {};

    bool operator<(const Edge &b) const { return m_weight < b.m_weight; }
};

void kruskalMSP(vector<Edge> &graph);

unsigned globalV;

vector<uint64_t> twoPowers{
        2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
        1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
        1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472,
        274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416,
        35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624,
        2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
        72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976};

int main() {
    unsigned t;
    scanf("%u", &t);


    ///go through test cases
    for (int i = 0; i < t; ++i) {

        /// v and e (v <2, 10^5>  e < 1 ,  2* 10^5>) E:100 000 V:200 000
        unsigned v, e;
        scanf("%u%u", &v, &e);
        globalV = v;
        vector<Edge> graph;

        /// scan graph (200 000 operations)
        for (int j = 0; j < e; ++j) {
            unsigned nodeA, nodeB;
            uint64_t value;
            scanf("%u%u%lu", &nodeA, &nodeB, &value);

            /// make weight smaller ( max. 59 steps)
            //int cnt = 0;
            //for (; value - 1; ++cnt)
              //  value >>= 1;

            unsigned cnt = (unsigned) (lower_bound(twoPowers.begin(), twoPowers.end(), value) - twoPowers.begin());

            ///sort O(n*log n) 200 000 numbers
            graph.emplace_back(Edge(nodeA - 1, nodeB - 1, cnt+1));
        }

        /// sort and kruskal it
        sort(graph.begin(), graph.end());
        kruskalMSP(graph);
    }
}

struct UnionNode {
    int m_parent;
    int m_rank;

    UnionNode(int parent) : m_parent(parent), m_rank(0) {};
};

int findParrent(int x, vector<UnionNode> &union_rank) {
    if (x != union_rank[x].m_parent)
        union_rank[x] = findParrent(union_rank[x].m_parent, union_rank);
    return union_rank[x].m_parent;
}

void unionInsert(int x, int y, vector<UnionNode> &union_rank) {
    int rootX = findParrent(x, union_rank);
    int rootY = findParrent(y, union_rank);

    if (union_rank[rootX].m_rank < union_rank[rootY].m_rank)
        union_rank[rootX].m_parent = rootY;

    else if (union_rank[rootX].m_rank > union_rank[rootY].m_rank)
        union_rank[rootY].m_parent = rootX;

    else {
        union_rank[rootY].m_parent = rootX;
        union_rank[rootX].m_rank++;
    }
}

/// toto cele by melo take bezet  O(e * log e )
/// nejhure projdi 200 000 uzlu
/// pro kazdy vyhledej log n predchudce. (udajne log n) ja to nedokazu spocitat
void kruskalMSP(vector<Edge> &graph) {
    vector<UnionNode> unionRank;
    for (int i = 0; i < globalV; ++i)
        unionRank.emplace_back(UnionNode(i));

    unsigned finalCount = 0;
    int cnt = 0;
    for (auto &edge : graph) {
        int parentA = findParrent(edge.m_nodeA, unionRank);
        int parentB = findParrent(edge.m_nodeB, unionRank);

        if (parentA != parentB) {
            unionInsert(parentA, parentB, unionRank);
            finalCount += edge.m_weight;
            cnt++;
        }

        if (cnt == globalV - 1)
            break;
    }
    if(finalCount)
        finalCount++;
        printf("%u\n", finalCount);
}