// hihocoder 1093

#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 100000 + 1024;

struct Dijkstra {
    struct HeapNode {
        int u, d;
        HeapNode() {}
        HeapNode(int u, int d): u(u), d(d) {}
        bool operator < (const HeapNode &rhs) const {
            return d > rhs.d;
        }
    };
    priority_queue<HeapNode> Q;
    vector<pair<int, int> > G[N];
    int dist[N];
    bool done[N];

    void init(int n) {
        for(int i = 0; i <= n; ++i) G[i].clear();
    }

    void add_edge(int u, int v, int c) {
        G[u].push_back(make_pair(v, c));
    }

    void dijkstra(int s) {
        memset(done, false, sizeof(done));
        memset(dist, 0x3F, sizeof(dist));
        while(!Q.empty()) Q.pop();
        Q.push(HeapNode(s, 0));
        dist[s] = 0;
        while(!Q.empty()) {
            HeapNode pre = Q.top(); Q.pop();
            if(done[pre.u]) continue;
            done[pre.u] = true;
            for(int i = 0; i < G[pre.u].size(); ++i) {
                pair<int, int> &e = G[pre.u][i];
                if(dist[e.first] > dist[pre.u] + e.second) {
                    dist[e.first] = dist[pre.u] + e.second;
                    Q.push(HeapNode(e.first, dist[e.first]));
                }
            }
        }
    }
} dijkstra;

struct Spfa {
    bool inq[N];
    int dist[N];
    vector<pair<int, int> > G[N];
    queue<int> Q;
    void init(int n) {
        for(int i = 0; i <= n; ++i) G[i].clear();
    }
    void add_edge(int u, int v, int c) {
        G[u].push_back(make_pair(v, c));
    }

    void spfa(int s) {
        memset(inq, false, sizeof(inq));
        memset(dist, 0x3F, sizeof(dist));
        while(!Q.empty()) Q.pop();
        dist[s] = 0;
        inq[s] = true;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for(int i = 0; i < G[u].size(); ++i) {
                pair<int, int> &e = G[u][i];
                if(dist[e.first] > dist[u] + e.second) {
                    dist[e.first] = dist[u] + e.second;
                    if(!inq[e.first]) {
                        inq[e.first] = true;
                        Q.push(e.first);
                    }
                }
            }
        }
    }
} spfa;

int main(int argc, char **argv) {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    dijkstra.init(n);
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        dijkstra.add_edge(u, v, c);
        dijkstra.add_edge(v, u, c);
    }
    dijkstra.dijkstra(s - 1);
    printf("%d\n", dijkstra.dist[t - 1]);
    return 0;
}

/**
5 10 3 5
1 2 997
2 3 505
3 4 118
4 5 54
3 5 480
3 4 796
5 2 794
2 5 146
5 4 604
2 5 63

*/

/**
172
*/
