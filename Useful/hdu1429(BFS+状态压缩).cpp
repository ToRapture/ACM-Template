#include<stdio.h>
#include<string.h>
#include<queue>
#define mt(a,b) memset(a,b,sizeof(a))
#define Rep(i,n) for(int i=1; i<=(n); ++i)
#define rep(i,n) for(int i=0; i<(n); ++i)
#define M 30
using namespace std;

struct node {
	int x,y;
	int key,t;
} S;
queue <node> q;
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
char pic[M][M];
bool vis[M][M][(1<<10) + 10];
int n,m,t;
bool ok( node &A ) {
	return A.x >= 0 && A.x < n && A.y >= 0 && A.y < m && !vis[A.x][A.y][A.key] && pic[A.x][A.y] != '*';
}
void solve( node &A ) {
	if(!ok(A)) return;
	char &tmp = pic[A.x][A.y];
	if(tmp >= 'a' && tmp <= 'z') 
		A.key |= 1 << tmp - 'a';
	if(tmp >= 'A' && tmp <= 'Z')
		if(!(A.key & (1 << tmp - 'A'))) return;
	if(!vis[A.x][A.y][A.key]) {
		vis[A.x][A.y][A.key] = true;
		q.push(A);
	}
}

int bfs() {
	mt(vis,0);
	while(!q.empty()) q.pop();
	S.key = S.t = 0;
	vis[S.x][S.y][S.key] = true;
	q.push(S);
	
	while(!q.empty()) {
		node pre = q.front(); q.pop();
		rep(i,4) {
			node now = pre;
			now.x += dx[i], now.y += dy[i];
			++now.t;
			if(pic[now.x][now.y] == '^' && now.t < t) return now.t;
			solve(now);
		}
	}
	
	return -1;
}	
int main() {
	while(~scanf("%d%d%d",&n,&m,&t)) {
		rep(i,n) {
			scanf("%s",pic[i]);
			rep(j,m) if(pic[i][j] == '@') S.x = i, S.y = j;
		}
		printf("%d\n",bfs());
	}
	return 0;
}
/*
4 5 17
@A.B.
a*.*.
*..*^
c..b*

4 5 111
@A.B.
.*.*.
.*.*^
cC.b*

1 4 11
@cC^

1 8 11
@abACcB^

2 8 111
@AABBCD^
a*b*cBd*

6 7 111
@aAbBC*
AAA.BC*
BBBBcC*
CCCCCC*
.******
......^
*/

/*
16
14
3
-1
13
19
*/