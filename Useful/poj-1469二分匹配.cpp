#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int N = 500;

vector<int> g[110];
int match[N];
bool vis[N];

bool dfs(int u) {
    for(int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if(!vis[v]) {
            vis[v] = true;
            if(match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int p,n;
        scanf("%d%d",&p,&n);
        for(int i = 1; i <= p; ++i)
            g[i].clear();
        memset(match,-1,sizeof(match));
        memset(vis,false,sizeof(vis));
        for(int i = 1; i <= p; ++i) {
            int c;
            scanf("%d",&c);
            while(c--) {
                int to;
                scanf("%d",&to);
                g[i].push_back(to);
            }
        }
        int ans = 0;
        for(int i = 1; i <= p; ++i)  {
            memset(vis,false,sizeof(vis));

            if(dfs(i)) {
                ++ans;
            }
        }
        puts(ans == p ? "YES" : "NO");
    }
    return 0;
}
/*
2
3 3
3 1 2 3
2 1 2
1 1
3 3
2 1 3
2 1 3
1 1
*/
