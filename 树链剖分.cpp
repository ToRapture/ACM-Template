// bzoj 2819 ��������

#include <bits/stdc++.h>
using namespace std;

struct TreeFucker {
    static const int MAXN = 500000 + 16;
    static const int INF = 0x7F7F7F7F;

    int head[MAXN], tot;
    int top[MAXN];  //top[v] ��ʾv���ڵ������Ķ��˽ڵ�
    int fa[MAXN];   //���׽ڵ�
    int deep[MAXN]; //���
    int num[MAXN];  //num[v]��ʾ��vΪ���������Ľڵ���
    int p[MAXN];    //p[v]��ʾv���߶����е�λ��
    int fp[MAXN];   //��p�����෴
    int son[MAXN];  //�ض���
    int pos;

    struct Edge {
        int to, next;
    } edge[MAXN << 1];

    void add_edge(int u, int v) {
        edge[tot].to = v;
        edge[tot].next = head[u];
        head[u] = tot++;
    }

    void dfs(int u, int pre, int d) {  //��һ��dfs���fa,deep,num,son
        deep[u] = d;
        fa[u] = pre;
        num[u] = 1;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(v != pre) {
                dfs(v, u, d + 1);
                num[u] += num[v];
                if(son[u] == -1 || num[v] > num[son[u]]) son[u] = v;
            }
        }
    }
    void getpos(int u, int sp) {
        top[u] = sp;
        p[u] = pos++;
        fp[p[u]] = u;
        if(son[u] == -1) return;
        getpos(son[u], sp);
        for(int i = head[u]; i != -1 ; i = edge[i].next) {
            int v = edge[i].to;
            if(v != son[u] && v != fa[u]) getpos(v, v);
        }
    }

    struct TreeNode {
        int sum;
    } tree[MAXN << 2];

    #define lrrt int L, int R, int rt
    #define lson L, mid, rt << 1
    #define rson mid + 1, R, rt << 1 | 1
    #define iall 1, pos, 1

    void push_up(int rt) {
        tree[rt].sum = tree[rt << 1].sum ^ tree[rt << 1 | 1].sum;
    }

    void build(lrrt) {
        if(L == R) {
            tree[rt].sum = data[fp[L]];
        } else {
            int mid = L + R >> 1;
            build(lson);
            build(rson);
            push_up(rt);
        }
    }

    void update(lrrt, int x, int val) {
        if(L == R) {
            tree[rt].sum = val;
        } else {
            int mid = L + R >> 1;
            if(x <= mid) update(lson, x, val);
            else update(rson, x, val);
            push_up(rt);
        }
    }

    int querySum(lrrt, int x, int y) {
        if(x <= L && R <= y) {
            return tree[rt].sum;
        } else {
            int mid = L + R >> 1;
            int ans = 0;
            if(x <= mid) ans ^= querySum(lson, x, y);
            if(y >  mid) ans ^= querySum(rson, x, y);
            return ans;
        }
    }

public:

    int data[MAXN];

    void init() {   //��ʼ��
        tot = 0;
        pos = 1;
        memset(head, -1, sizeof(head));
        memset(son, -1, sizeof(son));
    }

    void work(int root = 1) {   //����dfsά������Ϣ
        dfs(root, -1, 0);
        getpos(root, root);
        build(iall);
    }
    void update(int x, int val) {   //��xλ�õ�ֵ�޸�Ϊval
        update(iall, p[x], val);
    }
    int findSum(int u, int v) { //��ѯu->v·���Ͻڵ��Ȩֵ��xor�ͣ�������Ҫ�޸�
        int f1 = top[u], f2 = top[v];
        int tmp = 0;
        while(f1 != f2) {   //��u��v����һ������
            if(deep[f1] < deep[f2]) {
                swap(f1, f2); swap(u, v);
            }
            tmp ^= querySum(iall, p[f1], p[u]);
            u = fa[f1];
            f1 = top[u];
        }
        if(deep[u] > deep[v]) swap(u, v);
        return tmp ^ querySum(iall, p[u], p[v]);
    }
    #undef lrrt
    #undef lson
    #undef rson
    #undef iall
} fucker;

int main(int argc, char **argv) {
    int n;
    while(~scanf("%d", &n)) {
        fucker.init();
        for(int i = 1; i <= n; ++i) scanf("%d", &fucker.data[i]);
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            fucker.add_edge(u, v);
            fucker.add_edge(v, u);
        }
        fucker.work();
        int Q;
        scanf("%d", &Q);
        while(Q--) {
            char op[2];
            int x, y;
            scanf("%s%d%d", op, &x, &y);
            if(op[0] == 'Q') puts(fucker.findSum(x, y) ? "Yes" : "No");
            else fucker.update(x, y);
        }
    }
    return 0;
}

