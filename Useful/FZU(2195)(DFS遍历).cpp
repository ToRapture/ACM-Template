#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 1100010
using namespace std;

struct G {      //链式向前星存图
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

int dfs(int u,int pre) {        //深搜到每个叶子节点，返回到达各叶子节点的最大边权和
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
        printf("%d\n",sum - dfs(1,-1));     //不从代价最高的叶子节点回溯
    }
    return 0;
}
