#include<cstdio>
#include<cstring>
#include<algorithm>
#define lrrt int L,int R,int rt
#define imid int mid = (L+R) >> 1
#define lson L,mid,rt<<1
#define rson mid+1,R,rt<<1|1
#define iall 1,m,1
#define M 200005
using namespace std;

int tree[M << 2];
bool vis[M];
int uniq[M];    //����ȥ�غ������˵�����
int ans;
struct {
    int l,r;    //ÿ��������������
} op[M];

void pushdown(int rt) {
    if(~tree[rt]) {
        tree[rt<<1] = tree[rt<<1|1] = tree[rt];
        tree[rt] = -1;
    }
}

void update(int x,int y,int c,lrrt) {
    if(x <= L && R <= y) {
        tree[rt] = c;
        return;
    }
    pushdown(rt);
    imid;
    if(x <= mid) update(x,y,c,lson);
    if(y  > mid) update(x,y,c,rson);		//û��pushup����
}

void query(int x,int y,lrrt) {
    if(~tree[rt]) {
        if(!vis[ tree[rt] ] ) ++ans;
        vis[ tree[rt] ] = true;
        return;
    }
    if(L == R) return; //tree[rt] == -1
    imid;
    if(x <= mid) query(x,y,lson);
    if(y >  mid) query(x,y,rson);
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n;
        scanf("%d",&n);
        int m = 0;  //mΪ����������Ԫ�ظ���
        for(int i=1; i<=n; ++i) {
            scanf("%d%d",&op[i].l,&op[i].r);
            uniq[++m] = op[i].l;        //��uniq[1]��ʼʹ�ø�����
            uniq[++m] = op[i].r;
        }
        sort(uniq+1, uniq+m+1);
        m = unique(uniq+1,uniq+m+1) - (uniq+1);   //ȥ��


        for(int i=m; i>1; --i) {
            if(uniq[i] != uniq[i-1]+1)
                uniq[++m] = uniq[i-1] + 1;
        }

        /*
            ��������1������[x,y]֮�����a��a��(x,y)
            �������иò���
            1: [1,10],[1,4],[5,10] ��Ϊ[1,2](2),[3,4](3)��û������
            2: [1,10],[1,4],[6,10] ��Ϊ[1,2](2),[3,4](3), ����ȷ��ʽӦΪ[1,2](2),[2,3](1),[3,4](3)
            2�Ľ�����������̲������Ϊ[1,3](2),[3,5](1),[5,7](3)
        */
        sort(uniq+1,uniq+m+1);

        memset(tree,-1,sizeof(tree));
        memset(vis,false,sizeof(vis));
        ans = 0;

        for(int i=1; i<=n; ++i) {
            int l = lower_bound(uniq+1,uniq+m+1,op[i].l) - uniq;        //���ֲ����±�
            int r = lower_bound(uniq+1,uniq+m+1,op[i].r) - uniq;
            update(l,r,i,iall);
        }
        query(1,m,iall);
        printf("%d\n",ans);
    }
    return 0;
}
/*
1
5
1 4
2 6
8 10
3 4
7 10
*/
