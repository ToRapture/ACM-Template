#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

const int N = 505;
const int inf = 0x7F7F7F7F;

int n,m,s,t,dis[N],pre[N],gap[N],flow[N][N];

struct edge {
	int v,w;
	edge *next,*rev;
	edge() { next = NULL; }
	edge(int v, int w, edge *next) :
		v(v), w(w), next(next) {}
} *adj[N], *path[N], *e;

void Insert(int u,int v,int w) {
	edge *p = new edge(v, w, adj[u]);
	adj[u] = p;
	edge *q = new edge(u, 0, adj[v]);
	adj[v] = q;
	p->rev = q;
	q->rev = p;
}
void bfs() {
	memset(dis, 0x7f, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	queue<int> q;
	dis[t] = 0;
	gap[0] = 1;
	q.push(t);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(e = adj[x]; e != NULL; e = e->next) {
			if(e->rev->w == 0 || dis[e->v] < t) continue;
			dis[e->v] = dis[x] + 1;
			++gap[dis[e->v]];
			q.push(e->v);
		}
	}
}
int ISAP() {
	memset(dis, 0, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	bfs();
	int ans = 0, u = s, d;
	while(dis[s] <= t) {
		if(u == t) {
			int minflow = -1u >> 1;
			for(e = path[u]; u != s; e = path[u = pre[u]])
				minflow = min(minflow, e->w);
			for(e = path[u = t]; u != s; e = path[u = pre[u]]) {
				e->w -= minflow;
				e->rev->w += minflow;
				flow[pre[u]][u] += minflow;
				flow[u][pre[u]] -= minflow;
			}
			ans += minflow;
		}
		for(e = adj[u]; e != NULL; e = e->next)
			if(e->w > 0 && dis[u] == dis[e->v] + 1) break;
		if(e != NULL) {
			pre[e->v] = u;
			path[e->v] = e;
			u = e->v;
		} else {
			if(--gap[dis[u]] == 0) break;
			for(d = t,e = adj[u]; e != NULL; e = e->next)
				if(e->w > 0) d = min(d,dis[e->v]);
			dis[u] = d + 1;
			++gap[dis[u]];
			if(u != s) u = pre[u];
		}
	}
	return ans;
}
int main() {
	int u,v,w;
	while(~scanf("%d%d",&m,&n)) {
		memset(adj,0,sizeof(adj));
		while(m--) {
			scanf("%d%d%d",&u,&v,&w);
			Insert(u,v,w);
			//Insert(v,u,w);//ÎÞÏò±ß
		}
		s = 1;
		t = n;
		printf("%d\n",ISAP());
	}
}
/*
6 5
3 4 5
4 5 5
1 2 10
2 3 10
1 3 20
2 5 20

*/

