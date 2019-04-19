#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 10000 + 1024;
const int M = 1000000 + 1024;

struct Edge {
    int to, next;
    bool cut;   //是否为桥的标记
} edge[M];

int n, m;
int head[N], tot;
int LOW[N], DFN[N], STACK[N], index, top;
bool INS[N], cut[N];
int add_block[N];    //删除一个点后增加的连通块
int bridge;

void add_edge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].cut = false;
    head[u] = tot++;
}

void tarjan(int u, int pre) {
    int v;
    LOW[u] = DFN[u] = ++index;
    STACK[top++] = u;
    INS[u] = true;
    int son = 0;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        v = edge[i].to;
        if(v == pre) continue;
        if(!DFN[v]) {
            ++son;
            tarjan(v, u);
            if(LOW[u] > LOW[v]) LOW[u] = LOW[v];
            if(LOW[v] > DFN[u]) {
                ++bridge;
                edge[i].cut = true;
                edge[i ^ 1].cut = true;
            }
            if(u != pre && LOW[v] >= DFN[u]) {  //不是树根
                cut[u] = true;
                ++add_block[u];
            }

        } else if(LOW[u] > DFN[v]) {
            LOW[u] = DFN[v];
        }
    }
    if(u == pre && son > 1) cut[u] = true;  //树根，分支数大于1
    if(u == pre) add_block[u] = son - 1;
    INS[u] = false;
    top--;
}
void solve() {
    memset(DFN, 0, sizeof(DFN));
    memset(INS, false, sizeof(INS));
    memset(add_block, 0, sizeof(add_block));
    memset(cut, false, sizeof(cut));
    index = top = 0;
    bridge = 0;

    int cnt = 0;
    for(int i = 0; i < n; i++) if(!DFN[i]) {    //如果从1开始则[1, n]
        tarjan(i, i);
        ++cnt;
    }
    int ans = 0;    //求删除一个点后，图中最多有多少个连通块

    for(int i = 0; i < n; ++i)      //如果从1开始则[1, n]
        ans = max(ans, cnt + add_block[i]);

    cout << ans << endl;
}
void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}


int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    while(cin >> n >> m, n | m) {
        init();
        while(m--) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v); //无向图，所以添加两条边
            add_edge(v, u);
        }
        solve();
    }
    return 0;
}


/**
poj 2117

3 3
0 1
0 2
2 1
4 2
0 1
2 3
3 1
1 0
0 0

*/

/**
1
2
2
*/

/**
10 8
0 1
0 2
1 2
2 3
3 4
4 5
4 6
5 6
0 0

*/
