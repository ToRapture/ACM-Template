#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 5000 + 128;
const int M = 20000 + 1024;

struct Edge {
    int to, next;
    bool cut;
} edge[M];

int head[N], tot;
int n, m, LOW[N], DFN[N], STACK[N], BELONG[N];
int index, top;
int block, bridge;
bool INS[N];

void add_edge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].cut = false;
    head[u] = tot++;
}

void tarjan(int u, int pre) {
    LOW[u] = DFN[u] = ++index;
    STACK[top++] = u;
    INS[u] = true;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v == pre) continue;
        if(!DFN[v]) {
            tarjan(v, u);
            if(LOW[u] > LOW[v]) LOW[u] = LOW[v];
            if(LOW[v] > DFN[u]) {
                ++bridge;
                edge[i].cut = edge[i ^ 1].cut = true;
            }
        } else if(INS[v] && LOW[u] > DFN[v]) {
            LOW[u] = DFN[v];
        }
    }
    if(LOW[u] == DFN[u]) {
        ++block;
        int v;
        do {
            v = STACK[--top];
            INS[v] = false;
            BELONG[v] = block;
        } while(u != v);
    }
}

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

int degree[N];

void solve() {
    memset(DFN, 0, sizeof(DFN));
    memset(INS, false, sizeof(INS));
    index = top = block = bridge = 0;
    for(int i = 1; i <= n; ++i) if(!DFN[i]) tarjan(i, i);
    memset(degree, 0, sizeof(degree));

    for(int i = 1; i <= n; ++i)
    for(int j = head[i]; j != -1; j = edge[j].next)
    if(edge[j].cut) ++degree[BELONG[i]];

    int cnt = 0;
    for(int i = 1; i <= block; ++i) if(degree[i] == 1) ++cnt;
    cout << (cnt + 1) / 2 << endl;
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    while(cin >> n >> m) {
        init();
        while(m--) {
           int u, v;
           cin >> u >> v;
           add_edge(u, v);
           add_edge(v, u);
        }
        solve();
    }
    return 0;
}

/**
poj 3177

7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7

*/

/**
2
*/
