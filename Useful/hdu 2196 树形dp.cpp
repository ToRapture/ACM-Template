#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define Rep(i, n) for (int i = 1; i <= (n); ++i)
#define mt(a, b) memset(a, b, sizeof(a))
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 10000 + 1024;
struct Edge {
    int v, c;
};
int n;
vector<int> G[N];
vector<Edge> edges;
LL dp[N][2];
bool vis[N];

LL pre_dfs(int u) {
    vis[u] = true;
    for (int i = 0; i < G[u].size(); ++i) {
        Edge &e = edges[G[u][i]];
        if(vis[e.v]) continue;
        dp[u][0] = max(dp[u][0], pre_dfs(e.v) + e.c);
    }
    return dp[u][0];
}

void dfs(int u) {
    vis[u] = true;
    LL Max1 = 0, Max2 = 0;
    int v1 = -1, v2 = -1;
    for(int i = 0; i < G[u].size(); ++i) {
        Edge &e = edges[G[u][i]];
        if(vis[e.v]) continue;
        LL tmp = dp[e.v][0] + e.c;
        if(tmp > Max1) {
            Max2 = Max1;
            v2 = v1;
            Max1 = tmp;
            v1 = e.v;
        } else if(tmp == Max1 || tmp > Max2) {
            Max2 = tmp;
            v2 = e.v;
        }
    }

    if(u != 1) {
        LL tmp = dp[u][1];
        if(tmp > Max1) {
            Max2 = Max1;
            v2 = v1;
            Max1 = tmp;
            v1 = -2;
        } else if(tmp == Max1 || tmp > Max2) {
            Max2 = tmp;
            v2 = -2;
        }
    }

    for (int i = 0; i < G[u].size(); ++i) {
        Edge &e = edges[G[u][i]];
        if(vis[e.v]) continue;
        if(v1 != e.v && v1 != -1) {
            dp[e.v][1] = Max1 + e.c;
        } else if(v2 != e.v && v2 != -1) {
            dp[e.v][1] = Max2 + e.c;
        } else {
            dp[e.v][1] = e.c;
        }
        dfs(e.v);
    }
}

int main(int argc, char **argv) {
    while(cin >> n) {
        for(int i = 1; i <= n; ++i) G[i].clear();
        edges.clear();
        for(int i = 2; i <= n; ++i) {
            int v, c;
            cin >> v >> c;
            edges.push_back((Edge){v, c});
            edges.push_back((Edge){i, c});
            int size = edges.size();
            G[i].push_back(size - 2);
            G[v].push_back(size - 1);
        }
        memset(dp, 0, sizeof(dp));
        memset(vis, false, sizeof(vis));
        pre_dfs(1);
        memset(vis, false, sizeof(vis));
        dfs(1);
        for(int i = 1; i <= n; ++i)
            cout << max(dp[i][0], dp[i][1]) << endl;
    }
    return 0;
}

/**
5
1 1
2 1
3 1
1 1

*/

/**
3
2
3
4
4
*/
