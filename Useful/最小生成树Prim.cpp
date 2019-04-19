#include<cstdio>
#include<cstring>
#include<iostream>
#define MAXN 1005
#define INF 0x7f7f7f7f
using namespace std;
int N;
int edge[MAXN][MAXN];
int cost[MAXN];
bool vis[MAXN];
int prim() {
    int ans = 0;
    int Min;
    int pos = 0;
	memset(vis,false,sizeof(vis));
    vis[pos] = true;
    for(int i=0; i<N; i++)
        cost[i] = edge[pos][i];
    int nVex = 1;
    while(nVex++ < N) {
        Min = INF;
        for(int i=0; i<N; i++) {
            if(!vis[i] && cost[i] < Min) {
                Min = cost[i];
                pos = i;
            }
        }
        vis[pos] = true;

        ans += Min;
        for(int j=0; j<N; j++) {
            cost[j] = min(edge[pos][j],cost[j]);
        }
    }
    return ans;
}

int main() {
    scanf("%d",&N);
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%d",&edge[i][j]);
    printf("%d\n",prim());
    return 0;
}
