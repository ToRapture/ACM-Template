#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int N = 1e4 + 10;

int degree[N] = { 0 };
bool vis[N] = { false };
vector<int> g[N];

int tot = 0;

void dfs(int u, int pre) {
    vis[u] = true;
    ++tot;
    for(int i=0; i<g[u].size(); ++i) {
        int v = g[u][i];
        if(!vis[v] && pre != v)
            dfs(v,u);
    }
}

int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int u,v;
    while(m--) {
        scanf("%d %d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
        ++degree[u], ++degree[v];
    }
    dfs(1,-1);
    bool flag = n == tot;
    if(flag) {
        int cnt = 0;
        for(int i=1; i<=n; ++i) {
            if(degree[i] & 1) {
                ++cnt;
                if(cnt > 2) {
                    flag = false;
                    break;
                }
            }
        }
        if(cnt != 2 && cnt != 0) flag = false;
        printf(flag ? "Full\n" : "Part\n");
    }
    else {
        printf("Part\n");
    }
    return 0;
}
