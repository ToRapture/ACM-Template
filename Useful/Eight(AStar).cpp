//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); ++i)
#define Rep(i,n) for(int i=1; i<=(n); ++i)
#define mt(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pb push_back
#define ALL(c) (c).begin(), (c).end()
#define sqr(x) ((x)*(x))
#define TP(x) typeof(x)
#define all(v,it) TP((v).begin()) it = (v).begin(); it != (v).end(); ++it
#define OUT(x) cout << #x << " = " << x << endl
using namespace std;
#ifndef __int64
typedef long long LL;
typedef unsigned long long ULL;
#else
typedef __int64 LL;
typedef unsigned __int64 ULL;
#endif

const int N = 1000000;

int fac[] = {1,1,2,6,24,120,720,5040,40320,362880};
int dx[] = {0,-1,0,1};	//lurd
int dy[] = {-1,0,1,0};

const char *Move = "lurd";
const int aim = 46234;
bool vis[N];
int start[16];

struct Node {
	int s[9];
	int loc,g,h;
	int hash;
	string path;
	bool operator < (const Node &rhs) const {
		if(h == rhs.h) return g + h > rhs.g + rhs.h;
		else return h > rhs.h;
	}
};

int cantor(int s[]) {
	int sum = 0;
	for(int i = 0; i < 9; ++i) {
		int num = 0;
		for(int j = i + 1; j < 9; ++j)
			if(s[j] < s[i]) ++num;
		sum += (num * fac[9-i-1]);
	}
	return sum + 1;
}

bool isok(int s[]) {
    int sum = 0;  
    for(int i = 0;i < 9; i++)  
        for(int j = i + 1; j < 9; ++j)  
            if(s[j] && s[i] && s[i] > s[j]) ++sum;  
    return !(sum & 1);
}  

int get_h(Node &now) {
	int sum = 0;
	for(int i = 0; i < 9; ++i) {
		int x = i / 3;
		int y = i % 3;
		int xx,yy;
		if(now.s[i] == 0) {
			xx = yy = 2;
		} else {
			xx = (now.s[i] - 1) / 3;
			yy = (now.s[i] - 1) % 3;
		}
		sum += abs(xx - x) + abs(yy - y);
	}
	return sum;
}

void bfs() {
	Node st;
	for(int i = 0; i < 9; ++i) {
		st.s[i] = start[i];
		if(start[i] == 0) st.loc = i;
	}
	st.g = 0;
	st.h = get_h(st);
	st.hash = cantor(st.s);
	priority_queue<Node> q;
	mt(vis, false);
	vis[st.hash] = true;
	q.push(st);
	while(!q.empty()) {
		Node pre = q.top();
		q.pop();
		if(pre.hash == aim) {
			puts(pre.path.c_str());
			return;
		}
		for(int dir = 0; dir < 4; ++dir) {
			Node now = pre;
			now.path += Move[dir];
			++now.g;
			int x = now.loc / 3 + dx[dir], y = now.loc % 3 + dy[dir];
			if(!(x >= 0 && x < 3 && y >= 0 && y < 3)) continue;
			now.loc = x * 3 + y;
			swap(now.s[now.loc], now.s[pre.loc]);
			now.hash = cantor(now.s);
			now.h = get_h(now);
			if(isok(now.s) && !vis[now.hash]) {
				vis[now.hash] = true;
				q.push(now);
			}
		}
	}
}


int main(int argc, char **argv) {
	char in[16];
	while(gets(in)) {
		int len = 0;
		for(int i = 0; in[i]; ++i) {
			if(in[i] >= '1' && in[i] <= '9') start[len++] = in[i] - '0';
			if(in[i] == 'x') start[len++] = 0;
		}
		if(isok(start)) bfs();
		else puts("unsolvable");
	}
	return 0;
}
/*
23415x768
*/


