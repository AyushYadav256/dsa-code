// Author: Ayush Yadav
// GitHub: https://github.com/AyushYadav256
// Description: Kruskal’s Algorithm using Union-Find to find MST

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);
    UnionFind uf(n);
    int mstWeight = 0;

    for (Edge e : edges) {
        if (uf.unionSet(e.u, e.v)) {
            mstWeight += e.weight;
            cout << "Edge added: " << e.u << " - " << e.v << " (" << e.weight << ")\n";
        }
    }

    return mstWeight;
}

int main() {
    int n = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };

    int totalWeight = kruskalMST(n, edges);
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
