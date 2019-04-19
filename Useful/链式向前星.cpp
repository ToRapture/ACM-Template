#include<cstdio>
#include<cstring>
#define M 100
#define mt(a,b) memset(a,b,sizeof(a))
struct G {		//链式向前星，后存储的边将先存储的边向前推
	struct E {
		int u,v,c,next;
	} e[M];
	int el, head[M];  //head[] 存放每个节点的最后一条边的编号  
	void init() {
		el = 0;
		mt(head,-1);
	}	
	void add(int u,int v,int c) {	//el从0开始，将第el条边加入，该边的next置位刚刚的与定点u相连的第一条边
		e[el].u = u, e[el].v = v, e[el].c = c, e[el].next = head[u];
		head[u] = el;		//与顶点u相连的第一条边置为第el条边
		el++;		//边数+1
	}
} g;

int main() {
	while(1) {
		int u,v,c;
		int nVexs;
		scanf("%d",&nVexs);
		g.init();
		while(~scanf("%d%d%d",&u,&v,&c))
			g.add(u,v,c);
		for(int i=1; i<=nVexs; ++i) {
			for(int j=g.head[i]; ~j; j=g.e[j].next)	//遍历该点的每一条边，每次循环后将该次遍历的边的next赋给j
				printf("%d--->%d : %d\n",g.e[j].u,g.e[j].v,g.e[j].c);
		}
	}
	return 0;
}
/*
6
1 4 3
2 4 5
1 2 2
1 3 5
1 5 7
3 5 6
3 7 2
5 6 8
6 3 6
*/
