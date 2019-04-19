#include <stdio.h>
#include <string.h>
#include <queue>
using std::queue;
const int N = 1e5 + 10;
int n,m;
struct G {
	int head[N];
	int inDegree[N];
	int addNum;
	queue<int> q;
	
	struct E {
		int u,v,next;
	} e[M];
	int tot;
	void Clear() {
		memset(head,-1,sizeof(head));
		memset(inDegree,0,sizeof(inDegree));
		tot = 0;
		addNum = 0;
	}
	void Add(int u,int v) {
		e[tot].next = head[u];
		e[tot].u = u, e[tot].v = v;
		++inDegree[v];
		head[u] = tot++;
	}
	bool Push() {
		while(!q.empty()) q.pop();
		for(int i=1; i<=n; ++i) {
			if(inDegree[i] == 0) {
				q.push(i);
				++addNum;
			}
		}
		return !q.empty();
	}
	bool Judge() {
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int edge = head[u]; ~edge; edge = e[edge].next) {
				--inDegree[e[edge].v];
				if(inDegree[e[edge].v] == 0) {
					q.push(e[edge].v);
					++addNum;
				}
			}
		}
		return addNum == n;
	}
} g;

int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		g.Clear();
		scanf("%d %d",&n,&m);
		for(int i=0; i<m; ++i) {
			int u,v;
			scanf("%d %d",&u,&v);
			g.Add(u,v);
		}
		if(!g.Push()) {
			printf("Wrong\n");
			continue;
		}
		printf("%s\n",g.Judge() ? "Correct" : "Wrong");
	}
    return 0;    
}