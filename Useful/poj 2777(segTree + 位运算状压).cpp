/*
Memory  Time
2732 KB	407 ms
线段树 + 二进制
本题中 | 相当于 ∪ 操作
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#define M 100010
#define iall 1,L,1
#define lrrt int L,int R,int rt
#define lson L,mid,rt<<1
#define rson mid+1,R,rt<<1|1
#define imid int mid = (L+R)>>1
using namespace std;
struct node {
    int lazy;
    int state;
} tree[M<<2];
void pushup(int rt) {
    tree[rt].state = tree[rt<<1].state | tree[rt<<1|1].state;     //根结点状态为左右子结点状态的并集
}
void build(lrrt) {
    tree[rt].lazy = 0;
    if(L == R) {
        tree[rt].state = 1;
        return;
    }
    imid;
    build(lson);
    build(rson);
    pushup(rt);
}
void pushdown(int mid,lrrt) {
    if(tree[rt].lazy) {
        tree[rt<<1].state = tree[rt<<1|1].state = tree[rt].lazy;
        tree[rt<<1].lazy = tree[rt<<1|1].lazy = tree[rt].lazy;
        tree[rt].lazy = 0;
    }
}
void update(int x,int y,int color,lrrt) {
    if(x <= L && R <= y) {
        tree[rt].state = 1<<(color-1);
        tree[rt].lazy = tree[rt].state;
        return;
    }
    imid;
    pushdown(mid,L,R,rt);
    if(mid >= x) update(x,y,color,lson);
    if(mid < y)  update(x,y,color,rson);
    pushup(rt);
}

int query(int x,int y,lrrt) {
    if(x <= L && R <= y)
        return tree[rt].state;
    int ans = 0;
    imid;
    pushdown(mid,L,R,rt);
    if(mid >= x) ans |= query(x,y,lson);
    if(mid < y)  ans |= query(x,y,rson);
    return ans;
}

int Count(int state, int T) {  //计算有多少种颜色
    int sum = 0;
    for(int i=0; i<T; ++i) {
        if(state & (1<<i))
            sum++;
    }
    return sum;
}
int main() {
    int L,T,O;
    while(~scanf("%d%d%d",&L,&T,&O)) {
        build(iall);
        char op[4];
        int i,j,k;
        while(O--) {
            scanf("%s%d%d",op,&i,&j);
            if(i > j)
                swap(i,j);
            if(op[0] == 'P')
                printf("%d\n",Count(query(i,j,iall),T));
            else  {
                scanf("%d",&k);
                update(i,j,k,iall);
            }
        }
    }
    return 0;
}
