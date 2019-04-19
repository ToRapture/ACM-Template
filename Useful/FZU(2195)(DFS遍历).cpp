#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 1100010
using namespace std;

struct G {      //��ʽ��ǰ�Ǵ�ͼ
    int head[M];
    struct edge {
        int v,c,next;
    } e[M];
    int tot;
    void init() {
        tot = 0;
        memset(head,-1,sizeof(head));
    }
    void add(int u,int v,int c) {
        e[tot].v = v, e[tot].c = c, e[tot].next = head[u];
        head[u] = tot++;
    }
} g;

int dfs(int u,int pre) {        //���ѵ�ÿ��Ҷ�ӽڵ㣬���ص����Ҷ�ӽڵ������Ȩ��
    int Max = 0;
    for(int i=g.head[u]; ~i; i=g.e[i].next) {
        int v = g.e[i].v;
        if(v == pre) continue;
        Max = max(Max, dfs(v,u) + g.e[i].c);
    }
    return Max;
}
int main() {
    int n;
    while(~scanf("%d",&n)) {
        g.init();
        int u,v,c;
        int sum = 0;
        for(int i=1; i<n; ++i) {
            scanf("%d%d%d",&u,&v,&c);
            g.add(u,v,c);
            g.add(v,u,c);
            sum += c;
        }
        printf("%d\n",sum - dfs(1,-1));     //���Ӵ�����ߵ�Ҷ�ӽڵ����
    }
    return 0;
}
