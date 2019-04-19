#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 100010
#define I 100000
using namespace std;
/*
    �Զ��󿪲��鼯����itemid��userid��cityid����һ��
    ��֮ǰ��uid��Ϊuid+I�� cid��Ϊcid+I    (IΪ100000)
*/
int father[M << 2];
int Find(int x) {
    if(father[x] != x) father[x] = Find(father[x]);
    return father[x];
}
void Union(int x,int y) {
    x = Find(x);
    y = Find(y);
    int MAX = max(x,y);
    int MIN = min(x,y);
    father[MIN] = MAX;
}
int main() {
    int n,m,q;
    while(~scanf("%d%d%d",&n,&m,&q)) {
        for(int i=0; i<=M*4; ++i)
            father[i] = i;
        int uid,iid,cid;
        while(n--) {
            scanf("%d%d",&iid,&cid);
            if(iid && cid)
                Union(iid,cid+I*2);
        }
        while(m--) {
            scanf("%d%d%d",&uid,&iid,&cid);
            if(!uid) {
                if(iid && cid) Union(iid,cid+I*2);
            } else if(!iid) {
                if(uid && cid) Union(uid+I,cid+I*2);
            } else if(!cid) {
                if(uid && iid) Union(iid,uid+I);
            } else {
                Union(uid+I,iid);
                Union(uid+I,cid+I*2);
            }
        }
        int op,num;
        while(q--) {
            scanf("%d%d",&op,&num);
            int temp;
            if(op == 0) temp = Find(num);
            else temp = Find(num+I);
            if(temp > I*2) {
                printf("%d\n",temp-I*2);
            } else printf("0\n");
        }

    }
    return 0;
}


