#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 10000 + 1024;

int n, m, scc, index, top, STACK[N], INS[N], DFN[N], LOW[N], BELONG[N];
vector<int> G[N];
void tarjan(int u) {
    DFN[u] = LOW[u] = ++index;
    INS[u] = true;
    STACK[top++] = u;
    for(int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if(!DFN[v]) {
            tarjan(v);
            LOW[u] = min(LOW[u], LOW[v]);
        } else if(INS[v]) {
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
    if(DFN[u] == LOW[u]) {
        ++scc;
        int v;
        do {
            v = STACK[--top];
			INS[v] = false;
            BELONG[v] = scc;
        } while(u != v);
    }
}

void solve() {
    index = scc = top = 0;
    memset(DFN, 0, sizeof(DFN));
    memset(INS, false, sizeof(INS));
    for(int i = 1; i <= n; ++i)	//如果从0开始则[0, n)
    if(!DFN[i])
        tarjan(i);
}

void init() {
    for(int i = 0; i <= n; ++i) G[i].clear();
}

void add_edge(int u, int v) {
    G[u].push_back(v);
}

int main(int argc, char **argv) {
    while(cin >> n >> m, n | m) {
        init();
        while(m--) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
        }
        solve();
        cout << (scc == 1 ? "Yes" : "No") << endl;
    }
    return 0;
}

/**
hdu 1269

3 3
1 2
2 3
3 1
3 3
1 2
2 3
3 2
0 0

*/

/**
Yes
No
*/
