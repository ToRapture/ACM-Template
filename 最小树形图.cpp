// uva 11865

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
/*
* 最小树形图
* int型
* 复杂度O(NM)
* 点从0开始
*/
const int INF = 0x3F3F3F3F;
const int MAXN = 64;
const int MAXM = 10000 + 128;

struct Edge {
    int u, v, cost, kbps;
} edges[MAXM], e[MAXM];

int pre[MAXN], id[MAXN], visit[MAXN], in[MAXN];
int zhuliu(int root, int n, int m, Edge edge[]) {
    int res = 0, u, v;
    while(true) {
        for(int i = 0; i < n; i++)
            in[i] = INF;
        for(int i = 0; i < m; i++)
            if(edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v]) {
                pre[edge[i].v] = edge[i].u;
                in[edge[i].v] = edge[i].cost;
            }
        for(int i = 0; i < n; i++)
            if(i != root && in[i] == INF)
                return -1; // 不存在最小树形图
        int tn = 0;
        memset(id, -1, sizeof(id));
        memset(visit, -1, sizeof(visit));
        in[root] = 0;
        for(int i = 0; i < n; i++) {
            res += in[i];
            v = i;
            while(visit[v] != i && id[v] == -1 && v != root) {
                visit[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1) {
                for(int u = pre[v]; u != v ; u = pre[u])
                    id[u] = tn;
                id[v] = tn++;
            }
        }
        if(tn == 0) break; // 没有有向环
        for(int i = 0; i < n; i++)
            if(id[i] == -1)
                id[i] = tn++;
        for(int i = 0; i < m;) {
            v = edge[i].v;
            edge[i].u = id[edge[i].u];
            edge[i].v = id[edge[i].v];
            if(edge[i].u != edge[i].v)
                edge[i++].cost -= in[v];
            else
                swap(edge[i],edge[--m]);
        }
        n = tn;
        root = id[root];
    }
    return res;
}

int n, m, cost;

bool test(int x) {
    int tot = 0;
    for(int i = 0; i < m; ++i)
        if(edges[i].kbps >= x) e[tot++] = edges[i];

    int res = zhuliu(0, n, tot, e);
    return res != -1 && res <= cost;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &cost);
        int L = 1, R = 1;
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d%d", &edges[i].u, &edges[i].v, &edges[i].kbps, &edges[i].cost);
            R = max(R, edges[i].kbps);
        }
        bool flag = false;
        while(L < R) {
            int M = L + (R - L + 1) / 2;
            if(test(M)) {
                L = M;
                flag = true;
            }
            else R = M - 1;
        }
        if(flag) printf("%d kbps\n", L);
        else puts("streaming not possible.");
    }
    return 0;
}

/**
3
3 4 300
0 1 128 100
1 2 256 200
2 1 256 200
0 2 512 300
3 4 500
0 1 128 100
1 2 256 200
2 1 256 200
0 2 512 300
3 4 100
0 1 128 100
1 2 256 200
2 1 256 200
0 2 512 300

*/

/**
128 kbps
256 kbps
streaming not possible.
*/
