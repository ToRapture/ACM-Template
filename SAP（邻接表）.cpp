const int MaxN = 2005;
const int MaxE = 400005;
const int INF = 0x3F3F3F3F;
struct Edge {
	int u,v,flow,cap,pre;
	Edge() {}
	Edge(int u,int v,int cap,int pre) :
		u(u),v(v),cap(cap),pre(pre),flow(0) {}
} edge[MaxE];

int head[MaxN],nEdge;

void addEdge(int u,int v,int cap) {
	edge[nEdge] = Edge(u,v,cap,head[u]);
	head[u] = nEdge++;
	edge[nEdge] = Edge(v,u,0,head[v]);
	head[v] = nEdge++;
}
void edgeInit() { //��ӱ�֮ǰҪ�ȳ�ʼ����
	nEdge = 0;
	memset(head,-1,sizeof(head));
}
struct MaxFlow {
	int st,ed,n,mx_flow;//��ʾ��㣬�յ㣬�ж��ٸ��㣬�����������Ƕ��١�
	int dis[MaxN],gap[MaxN],cur[MaxN],aug[MaxN],path[MaxN];
	//dis��ʾÿ����ľ����ǣ�gap��ʾ����Ϊi�ĵ��ж��ٸ���cur���ڵ�ǰ���Ż���
	//aug��¼�ҵ�������·������path��¼�ҵ�������·��·����
	MaxFlow() {}
	MaxFlow(int st,int ed,int n) :
		st(st),ed(ed),n(n) {
		init();
	}
	void init() {
		for(int i = 0; i < MaxN; ++i) {
			aug[i] = gap[i] = dis[i] = 0;
			cur[i] = head[i];
		}
		aug[st] = INF;
		gap[0] = n;
		mx_flow = 0;
	}
	int augment(int &point) { //�޸��ҵ�������·�ϵıߵ���������ǰ���޸�Ϊ��㡣
		for(int i = ed; i != st; i = edge[path[i]].u) {
			int Pair = path[i] ^ 1;
			edge[ path[i] ].flow += aug[ed];
			edge[ Pair ].flow -= aug[ed];
		}
		point = st;
		return aug[ed];
	}
	int solve() {
		int u = st;
		while(dis[st] < n) {
			if(u == ed) mx_flow += augment(u);
			bool flag = true;
			for(int i = head[u]; i != -1; i = edge[i].pre) {
				int v = edge[i].v;
				if(edge[i].cap-edge[i].flow > 0 && dis[u] == dis[v] + 1) {
					path[v] = i;
					cur[u] = i;
					aug[v] = min(aug[u], edge[i].cap - edge[i].flow);
					u = v;
					flag = false;
					break;
				}
			}
			if(flag) {
				if(--gap[dis[u]] == 0) return mx_flow;
				dis[u] = MaxN;
				for(int i = head[u]; i != -1; i = edge[i].pre) {
					int v = edge[i].v;
					if(edge[i].cap - edge[i].flow > 0) dis[u] = min(dis[u], dis[v] + 1);
				}
				gap[dis[u]]++;
				cur[u] = head[u];
				if(u != st) u = edge[path[u]].u;
			}
		}
		return mx_flow;
	}
} sap;
