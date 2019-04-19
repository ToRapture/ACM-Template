struct TwoSet {
    int n, S[N * 2], c;
    vector<int> G[N * 2];
    bool mark[N * 2];
    void init(int n) {
        this->n = n;
        for(int i = 0; i < 2 * n; ++i) G[i].clear();
        memset(mark, false, sizeof(mark));
    }
    bool dfs(int x) {
        if(mark[x ^ 1]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for(int i = 0; i < G[x].size(); ++i)
            if(!dfs(G[x][i])) return false;
        return true;
    }
    void add_clause(int x, int xval, int y, int yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }
    bool solve() {
        for(int i = 0; i < n * 2; i += 2) {
            if(!mark[i] && !mark[i + 1]) {
                c = 0;
                if(!dfs(i)) {
                    while(c > 0) mark[S[--c]] = false;
                    if(!dfs(i + 1)) return false;
                }
            }
        }
        return true;
    }
} solver;


struct TwoSet {
    vector<int> G[N * 2];
    stack<int> sk;
    int n, block, dfs_clock, pre[N * 2], low[N * 2], sccno[N * 2];

    void add_clause(int x, int xval, int y, int yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }
    void tarjan(int u) {
        pre[u] = low[u] = ++dfs_clock;
        sk.push(u);
        for(int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i];
            if(!pre[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if(!sccno[v])
                low[u] = min(low[u], pre[v]);
        }
        if(pre[u] == low[u]) {
            ++block;
            int v;
            do {
                v = sk.top(); sk.pop();
                sccno[v] = block;
            } while(u != v);
        }
    }
    bool solve() {
        memset(pre, 0, sizeof(int) * n * 2);
        memset(sccno, 0, sizeof(int) * n * 2);
        dfs_clock = block = 0;
        for(int i = 0; i < n * 2; ++i)
            if(!pre[i]) tarjan(i);
        for(int i = 0; i < n * 2; i += 2) {
            if(sccno[i] == sccno[i + 1]) return false;
        }
        return true;
    }
    void init(int n) {
        this->n = n;
        for(int i = 0; i < n * 2; ++i) G[i].clear();
    }
} solver;
