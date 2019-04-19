#include <stdio.h>
#define M 1000
#define INF 0x7F7F7F7F
struct edge {
	int u,v,c;
} e[M];
int nNode,nEdge,src;
int dist[M],pre[M];
bool Bellman() {
	for(int i=0; i<nNode; ++i)
		dist[i] = i == src ? 0 : INF;
	for(int i=0; i<nNode-1; ++i)
		for(int j=0; j<nEdge; ++j) {
			if(dist[ e[j].u ] + e[j].c < dist[ e[j].v ]) {
				dist[ e[j].v ] = dist[ e[j].u ] + e[j].c;
				pre[ e[j].v ] = e[j].u;
			}
		}
	for(int i=0; i<nEdge; ++i) {
		if(dist[ e[i].v ] > dist[ e[i].u ] + e[i].c)
			return false;
	}
	return true;
}
int main() {
	scanf("%d%d%d",&nNode,&nEdge,&src);
	for(int i=0; i<nEdge; ++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
	Bellman();
	return 0;
}