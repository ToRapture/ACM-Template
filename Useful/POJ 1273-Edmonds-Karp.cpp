#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 204;
const int INF = 0x3F3F3F3F;


int f[N][N];
int c[N][N];
int res[N];
int pre[N];
queue<int> q;

void init() {
    while(!q.empty()) q.pop();
    memset(f,0,sizeof(f));
    memset(c,0,sizeof(f));
}

int EK(int s,int t) {
    int ans = 0;
    while(1) {
        while(!q.empty()) q.pop();
        memset(res,0,sizeof(res));
        res[s] = INF;
        pre[s] = -1;
        q.push(s);
        while(!q.empty()) {
            int p = q.front();
            q.pop();
            for(int i = 1; i <= t; ++i) {
                if(!res[i] && f[p][i] < c[p][i]) {
                    q.push(i);
                    pre[i] = p;
                    res[i] = min(res[p], c[p][i] - f[p][i]);
                }
            }
        }
        if(res[t] == 0) break;
        int p = t;
        while(~pre[p]) {
            f[ pre[p] ][p] += res[t];
            f[p][ pre[p] ] -= res[t];
            p = pre[p];
        }
        ans += res[t];
    }
    return ans;
}

int main(int argc, char **argv) {
    int n,m;
    while(~scanf("%d%d",&m,&n)) {
        init();
        while(m--) {
            int u,v,cost;
            scanf("%d%d%d",&u,&v,&cost);
            c[u][v] += cost;
        }
        printf("%d\n",EK(1,n));
    }
    return 0;
}
