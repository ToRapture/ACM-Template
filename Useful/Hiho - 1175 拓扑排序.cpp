#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
const int M = 5e5 + 10;
const int Mod = 142857;

int sum = 0;
int inDegree[N] = { 0 };
int n,m,k;

struct Node {
	int vir;
	vector<int> child;
	Node() {
		vir = 0;
		child.clear();
	}
} node[N];

queue<int> q;

void bfs() {
	for(int i=1; i<=n; ++i) {
		if(inDegree[i] == 0) q.push(i);
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		sum += node[u].vir;
		sum %= Mod;
		for(int i = 0; i < node[u].child.size() ; ++i) {
			int v = node[u].child[i];
			node[v].vir += node[u].vir;
			node[v].vir %= Mod;
			if(--inDegree[v] == 0) q.push(v);
		}
	}
}

int main() {
	scanf("%d %d %d",&n,&m,&k);
	
	while(k--) {
		int vid;
		scanf("%d",&vid);
		++node[vid].vir;
	}
	
	while(m--) {
		int u,v;
		scanf("%d %d",&u,&v);
		++inDegree[v];
		node[u].child.push_back(v);
	}
	bfs();
	printf("%d\n",sum);
	return 0;
}
