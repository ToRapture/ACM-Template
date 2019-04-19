// uva 11354

#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int INF = 0x7F7F7F7F;
const int N = 50000 + 128;
const int MAXLGN = 64;

struct Edge {
    int u, v, c;
    bool operator < (const Edge &rhs) const {
        return c < rhs.c;
    }
};

int n, m, fa[N];
bool vis[N];
vector<Edge> edges;
vector<Edge> G[N];

int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

struct LCA {
    int depth[N], fa[N], cost[N];
    int anc[MAXLGN][N], maxcost[MAXLGN][N];

    void preprocess() {
        memset(anc, -1, sizeof(anc));
        memset(maxcost, -1, sizeof(maxcost));
        for(int u = 1; u <= n; ++u) {
            anc[0][u] = fa[u];
            maxcost[0][u] = cost[u];
        }
        for(int i = 1; (1 << i) <= n; ++i)
        for(int u = 1; u <= n; ++u)
            if(anc[i - 1][u] != -1) {
                int k = anc[i - 1][u];
                if(anc[i - 1][k] == -1) continue;
                anc[i][u] = anc[i - 1][k];
                maxcost[i][u] = max(maxcost[i - 1][u], maxcost[i - 1][k]);
            }
    }

    int query(int p, int q) {
        if(depth[p] < depth[q]) swap(p, q);
        int hibit;
        for(hibit = 1; (1 << hibit) <= depth[p]; ++hibit); --hibit;
        int ans = -INF;
        for(int i = hibit; i >= 0; --i)
            if(depth[p] - (1 << i) >= depth[q]) {
                ans = max(ans, maxcost[i][p]);
                p = anc[i][p];
            }
        if(p == q) return ans;
        for(int i = hibit; i >= 0; --i)
            if(anc[i][p] != -1 && anc[i][p] != anc[i][q] ) {
                ans = max(ans, maxcost[i][p]);
                p = anc[i][p];
                ans = max(ans, maxcost[i][q]);
                q = anc[i][q];
            }
        ans = max(ans, cost[p]);
        ans = max(ans, cost[q]);
        return ans;
    }
} lca;

void dfs(int u, int fa, int depth) {
    lca.depth[u] = depth;
    for(Edge &e: G[u]) {
        if(e.v == fa) continue;
        lca.fa[e.v] = u;
        lca.cost[e.v] = e.c;
        dfs(e.v, u, depth + 1);
    }
}

int main(int argc, char **argv) {
    bool flag = false;
    while(~scanf("%d%d", &n, &m)) {
        edges.clear();
        while(m--) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            edges.push_back((Edge){u, v, c});
        }
        sort(edges.begin(), edges.end());

        for(int i = 1; i <= n; ++i) {
            G[i].clear();
            fa[i] = i;
        }

        for(auto &e : edges) {
            int fu = Find(e.u);
            int fv = Find(e.v);
            if(fu != fv) {
                fa[fu] = fv;
                G[e.u].push_back((Edge){e.u, e.v, e.c});
                G[e.v].push_back((Edge){e.v, e.u, e.c});
            }
        }

        dfs(1, -1, 0);
        lca.preprocess();

        if(flag) puts("");
        flag = true;

        int q;
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", lca.query(u, v));
        }

    }
    return 0;
}


/**
4 5
1 2 10
1 3 20
1 4 100
2 4 30
3 4 10
2
1 4
4 1
2 1
1 2 100
1
1 2

*/


/**
20
20

100
*/


/**
7 6
1 6 6
1 7 100
1 3 8
1 2 2
2 5 10
2 4 1
6
1 6
1 7
6 2
1 5
5 3
2 3

*/


/**
6
100
6
10
10
8
*/
