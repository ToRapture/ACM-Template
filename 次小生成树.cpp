// hdu 4081

#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 1024;

struct Point {
    int x, y, p;
} p[N];

struct Edge {
    int u, v;
    double c;
    bool operator < (const Edge &rhs) const {
        return c < rhs.c;
    }
};

vector<Edge> edges;
int n, fa[N];

int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

inline double dist(int x, int y) {
    return sqrt((p[x].x - p[y].x) * (p[x].x - p[y].x) + (p[x].y - p[y].y) * (p[x].y - p[y].y));
}

vector<pair<int, double> > G[N];

double f[N][N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for(auto &e : G[u]) {
        int v = e.first;
        double w = e.second;
        if(vis[v]) continue;
        for(int i = 0; i < n; ++i)
            if(vis[i]) f[i][v] = f[v][i] = max(w, f[i][u]);
        dfs(v);
    }
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        edges.clear();
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].p);
            fa[i] = i;
            G[i].clear();
        }
        for(int i = 0; i < n; ++i) for(int j = i + 1; j < n; ++j)
            edges.push_back((Edge){i, j, dist(i, j)});
        sort(edges.begin(), edges.end());
        double sum = 0.0;
        for(auto &e : edges) {
            int fu = Find(e.u);
            int fv = Find(e.v);
            if(fu != fv) {
                fa[fu] = fv;
                sum += e.c;
                G[e.u].push_back(make_pair(e.v, e.c));
                G[e.v].push_back(make_pair(e.u, e.c));
            }
        }

        memset(f, 0, sizeof(f));
        memset(vis, false, sizeof(vis));
        dfs(0);
        double ans = 0.0;
        for(int i = 0; i < n; ++i) for(int j = i + 1; j < n; ++j) {
            ans = max(ans, (p[i].p + p[j].p) * 1.0 / (sum - f[i][j]));
        }
        printf("%.2f\n", ans);
    }
    return 0;
}


/**
2
4
1 1 20
1 2 30
200 2 80
200 1 100
3
1 1 20
1 2 30
2 2 40

*/

/**
65.00
70.00
*/