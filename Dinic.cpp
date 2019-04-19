struct Dinic {  //时间复杂度O(min(n * sqrt(n), sqrt(m)) * m)
    static const int maxn = 3000 + 16;
    static const int INF = 0x7F7F7F7F;
    struct Edge {
        int from, to, cap, flow;
        Edge(int from, int to, int cap, int flow):
            from(from), to(to), cap(cap), flow(flow) {}
        Edge() {}
    };
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn], cur[maxn];

    int n, m, s, t; //n与m不需要特殊赋值，s与t在调用主过程的时候传就可以

    void init(int n = maxn - 1) {
        this->n = n;
        for(int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }

    void add_edge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BFS() {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = true;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); ++i) {
                Edge &e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int &i = cur[x]; i < G[x].size(); ++i) {
            Edge &e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s, int t) {
        this->s = s; this->t = t;
        int flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
} Dinic;
