//#include <bits/stdc++.h>
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x7F7F7F7F;
const int maxn = 65536;
const int N = 128;

struct MCMF {
    int n,m;
	struct Edge {
		int from,to,cap,flow,cost;
	};
    vector<Edge> edges;
    vector<int> G[maxn];
    int d[maxn], p[maxn], a[maxn];
    bool inq[maxn];
    void init(int n) {
        this->n = n;
        for(int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap,int cost) {
        edges.push_back((Edge) {from,to,cap,0,cost});
        edges.push_back((Edge) {to,from,0,0,-cost});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool Spfa(int s,int t,int &flow,int &cost) {
        for(int i = 0; i <= n; ++i) {
            d[i] = INF;
            inq[i] = false;
        }
        d[s] = 0;inq[s] = true; p[s] = 0;a[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for(int i = 0; i < G[u].size(); ++i) {
                Edge &e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if(d[t] == INF) return false;
        flow += a[t];
        cost += d[t] * a[t];
        int u = t;
        while(u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    int Mincost(int s,int t) {
        int flow = 0, cost = 0;
        while(Spfa(s,t,flow,cost));
        return cost;
    }
} mcmf;

char pic[N][N];
typedef pair<int,int> pii;

inline int dist(pii &a, pii &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    int n,m;
    while(~scanf("%d%d",&n,&m), n|m) {
        for(int i = 0; i < n; ++i) scanf("%s",pic[i]);
        vector<pii> man,house;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j)
            if(pic[i][j] == 'm') man.push_back(make_pair(i,j));
            else if(pic[i][j] == 'H') house.push_back(make_pair(i,j));
        int ns = man.size() + house.size() + 2;
        int mans = man.size();
        int s = ns - 1, t = ns - 2;
        mcmf.init(ns);
        for(int i = 0; i < man.size(); ++i) {
            for(int j = 0; j < house.size(); ++j) {
                mcmf.AddEdge(i, mans + j, 1, dist(man[i],house[j]));
                if(i == 0) mcmf.AddEdge(mans + j, t, 1, 0);
            }
            mcmf.AddEdge(s, i, 1, 0);
        }
        printf("%d\n",mcmf.Mincost(s,t));
    }
    return 0;
}

