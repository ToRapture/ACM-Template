#include <stdio.h>
#include <string.h>
#define INF 0x3F3F3F3F
#define M 9
int graph[M][M] = 
	{{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
};
int val[M];
bool vis[M];

void work(int src) {
	for(int i=0; i<M; ++i) {
		vis[i] = false;
		val[i] = graph[src][i] == 0 ? INF : graph[src][i];
	}
	vis[src] = true;
	val[src] = 0;
	int T = M - 1;
	while(T--) {
		int u, Min = INF;
		for(int i=0; i<M; ++i) {		//选取离S集合最近的点加入
			if(!vis[i] && val[i] < Min) {
				u = i;
				Min = val[i];
			}
		}
		vis[u] = true;

		for(int i=0; i<M; ++i) {		//松弛过程
			if(!vis[i] && graph[u][i] != 0 && graph[u][i] + val[u] < val[i])
				val[i] = graph[u][i] + val[u];
		}
	}
}
void print() {
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < M; i++)
		printf("%d \t\t %d\n", i, val[i]);
}
int main() {
	//freopen("DJ","w",stdout);
	for(int i=0; i<M; ++i) {
		work(i);
		print();
	}
	return 0;
}
