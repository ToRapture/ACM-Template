#include<stdio.h>
#define M 1000
#define rep(i,n) for(int i=0; i<(n); ++i)
int a[M][M];		//不连通的初始化成INF
int path[M][M];
int graph[M][M];
void floyd() {
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j) {
			a[i][j] = graph[i][j];
			path[i][j] = -1;
		}
	rep(k,n) rep(i,n) rep(j,n) 
		if(a[i][j] > a[i][k] + a[k][j]) {
			a[i][j] = a[i][k] + a[k][j];
			path[i][j] = k;
		}
}

int main() {
	return 0;
}
