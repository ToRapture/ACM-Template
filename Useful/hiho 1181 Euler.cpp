#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int N = 5000;

struct Edge {
    int u,v,vis;
    Edge(int u,int v,int vis = 0) :
        u(u), v(v), vis(vis) {}
};

vector<int> g[N];
vector<Edge> e;
int degree[N] = { 0 };
int path[N];
int pathsize = 0;

void dfs(int u) {
    for(int i=0; i<g[u].size(); ++i) {
        int el = g[u][i];
        if(!e[el].vis) {
            e[el].vis = e[el ^ 1].vis = 1;
            dfs(e[el].v);
        }
    }
    path[pathsize++] = u;
}

int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int root = 1;
    while(m--) {
        int u,v;
        scanf("%d %d",&u,&v);
        e.push_back(Edge(u,v));
        e.push_back(Edge(v,u));
        g[u].push_back(e.size() - 2);
        g[v].push_back(e.size() - 1);
        ++degree[u], ++degree[v];
        if(degree[u] > 2 && degree[u] & 1) root = u;
        if(degree[v] > 2 && degree[v] & 1) root = v;
    }
    dfs(root);
    bool flag = false;
    for(int i=0; i<pathsize; ++i) {
        if(flag) putchar(' ');
        flag = true;
        printf("%d",path[i]);
    }
    puts("");
    return 0;
}
/*
8 10
1 5
1 2
2 6
5 6
2 7
2 3
3 7
3 4
3 8
4 8
*/

