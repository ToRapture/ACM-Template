// hihocoder 1069

#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 100000 + 1024;

int n, m, q;
map<string, int> mp;
map<int, string> pm;

int fa[N], ancester[N], ans[N];
vector<int> G[N];
vector<pair<int, int> > Q[N];
bool vis[N] = { false }, flag[N] = { false };

int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Union(int u, int v) {
    int fu = Find(u);
    int fv = Find(v);
    fa[fu] = fv;
}

void tarjan(int u) {
    ancester[u] = u;
    fa[u] = u;
    vis[u] = true;
    for(auto v : G[u]) {
        tarjan(v);
        Union(u, v);
        ancester[Find(u)] = u;
    }
    for(auto &q : Q[u]) {
        if(vis[q.first])
            ans[q.second] = ancester[Find(q.first)];
    }
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin >> m;
    n = 0;
    while(m--) {
        string a, b;
        cin >> a >> b;
        if(!mp.count(a)) mp[a] = ++n;
        if(!mp.count(b)) mp[b] = ++n;
        int u = mp[a];
        int v = mp[b];
        flag[v] = true;
        G[u].push_back(v);
        pm[mp[a]] = a;
        pm[mp[b]] = b;
    }

    cin >> q;

    for(int i = 0; i < q; ++i) {
        string a, b;
        cin >> a >> b;
        int u = mp[a];
        int v = mp[b];
        Q[u].push_back(make_pair(v, i));
        Q[v].push_back(make_pair(u, i));
    }

    for(int i = 1; i <= n; ++i)
    if(!flag[i]) {
        tarjan(i);
        break;
    }
    for(int i = 0; i < q; ++i)
        cout << pm[ans[i]] << endl;
    return 0;
}


/**
4
Adam Sam
Sam Joey
Sam Micheal
Adam Kevin
3
Sam Sam
Adam Sam
Micheal Kevin

*/

/**
Sam
Adam
Adam
*/
