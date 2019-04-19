#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#define mt(a,b) memset(a,(b),sizeof(a))
#define M 105
using namespace std;
struct node {
	int x,y;
	int k,t;
} S;
int n,m;
bool vis[M][M][100];
char pic[M][M];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
queue<node>q;
bool ok(node &A) {
	return A.x >= 0 && A.x < n && A.y >= 0 && A.y < m && pic[A.x][A.y] != '#' && !vis[A.x][A.y][A.k];
}
void solve(node &A) {
	if(!ok(A)) return;
	char ch = pic[A.x][A.y];
	if(ch == 'b') A.k |= 1 << 0;
	if(ch == 'y') A.k |= 1 << 1;
	if(ch == 'r') A.k |= 1 << 2;
	if(ch == 'g') A.k |= 1 << 3;
	if(ch == 'B') if(!(A.k & 1 << 0)) return;
	if(ch == 'Y') if(!(A.k & 1 << 1)) return;
	if(ch == 'R') if(!(A.k & 1 << 2)) return;
	if(ch == 'G') if(!(A.k & 1 << 3)) return;
	if(!vis[A.x][A.y][A.k]) {
		vis[A.x][A.y][A.k] = true;
		q.push(A);
	}
	
}
int bfs() {
	mt(vis,0);
	while(!q.empty()) q.pop();
	S.t = S.k = 0;
	vis[S.x][S.y][S.k] = true;
	q.push(S);
	while(!q.empty()) {
		node pre = q.front(); q.pop();
		for(int i=0; i<4; ++i) {
			node now = pre;
			++now.t;
			now.x += dx[i], now.y += dy[i];
			if(now.x >= 0 && now.x < n && now.y >= 0 && now.y < m && pic[now.x][now.y] == 'X') return now.t; //²»ÅÐ¶Ï·¶Î§»áWA
			solve(now);
		}
	}
	
	return -1;
}
int main() {
	while(~scanf("%d%d",&n,&m) && n|m) {
		for(int i=0; i<n; ++i) {
			scanf("%s",pic[i]);
			for(int j=0; j<m; ++j)
				if(pic[i][j] == '*') S.x = i, S.y = j;
		}
		int ans = bfs();
		~ans ? printf("Escape possible in %d steps.\n",ans) : puts("The poor student is trapped!");
	}
	return 0;
}
/*
1 9
*........
*/