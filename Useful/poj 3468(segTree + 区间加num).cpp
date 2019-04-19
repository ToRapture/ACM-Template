#include<cstdio>
#include<cstring>
#define lrrt int L,int R,int rt
#define lson L,mid,rt<<1
#define rson mid+1,R,rt<<1|1
#define imid int mid = (L+R)>>1
#define iall 1,n,1
#define M 100100
typedef long long LL;
struct node{
    LL sum,lazy;
} tree[M<<2];

void pushup(int rt) {
    tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}

void build(lrrt) {
    tree[rt].lazy = 0;
    if(L == R) {
        LL temp;
        scanf("%I64d",&temp);
        tree[rt].sum = temp;
        return;
    }
    imid;
    build(lson);
    build(rson);
    pushup(rt);
}
void pushdown(int mid, lrrt) {
    if(tree[rt].lazy) {
        tree[rt<<1].lazy += tree[rt].lazy;
        tree[rt<<1|1].lazy += tree[rt].lazy;
        tree[rt<<1].sum += (mid-L+1) * tree[rt].lazy;
        tree[rt<<1|1].sum += (R-mid) * tree[rt].lazy;
        tree[rt].lazy = 0;
    }
}
void update(int l,int r,int num,lrrt) {
    if(l <= L && R <= r) {
        tree[rt].sum += (R-L+1) * num;
        tree[rt].lazy += num;
        return;
    }
    imid;
    pushdown(mid,L,R,rt);
    if(mid >= l) update(l,r,num,lson);
    if(mid < r)  update(l,r,num,rson);
    pushup(rt);
}
LL query(int l,int r,lrrt) {
    if(l <= L && r >= R)
        return tree[rt].sum;
    imid;
    pushdown(mid,L,R,rt);
    LL ans = 0;
    if(mid >= l) ans += query(l,r,lson);
    if(mid < r)  ans += query(l,r,rson);
    return ans;
}

int main() {
    int n,k;
    while(~scanf("%d%d",&n,&k)) {
        build(iall);
        while(k--) {
            char op[4];
            int x,y,z;
            scanf("%s%d%d",op,&x,&y);
            if(op[0] == 'Q')
                printf("%I64d\n",query(x,y,iall));
            else {
                scanf("%d",&z);
                update(x,y,z,iall);
            }
        }
    }
    return 0;
}
