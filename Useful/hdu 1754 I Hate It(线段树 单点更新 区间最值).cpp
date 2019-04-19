/*
右移不能随意按位或1
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 200005
struct treeNode
{
    int left,right;
    int valve;
};
int max(int a, int b) {
    return a>b?a:b;
}
int arr[MAXN];
treeNode segTree[MAXN * 4];
void buildTree(int node,int left,int right) {  //OK
    segTree[node].left = left;
    segTree[node].right = right;
    if(left == right) {
        scanf("%d",&segTree[node].valve);
        getchar();
        //segTree[node].valve = arr[left];
       // cout<<segTree[node].valve<<endl;
    }
    else {
        buildTree(node<<1,left,(left+right)>>1);
        buildTree(node<<1|1,((left+right)>>1)+1,right);
        segTree[node].valve = max(segTree[node*2].valve,segTree[node*2+1].valve);
      //  cout<<segTree[node].valve<<endl;
    }
}
void update(int node,int index,int num) {
    if(index > segTree[node].right || index < segTree[node].left) return;
    if(segTree[node].left == segTree[node].right) {     //叶子结点
        segTree[node].valve = num;
       // printf("node %d.valve = %d\n",node,num);
        return;
    }
    segTree[node].valve = max(segTree[node].valve,num);
    //printf("node %d.valve = %d\n",node,segTree[node].valve);
    if(index <= segTree[node*2].right) update(node*2,index,num);
    else update(node*2+1,index,num);
}
int query(int node,int left,int right) {
    if(segTree[node].left == left && segTree[node].right == right)
        return segTree[node].valve;
    if(right <= segTree[node*2].right) return query(node*2,left,right);
    else if(left >= segTree[node*2+1].left) return query(node*2+1,left,right);
    else return max(query(node*2,left,segTree[node*2].right),query(node*2+1,segTree[node*2+1].left,right));
}
int main() {
    int nStudents,nInstructs;
    while(~scanf("%d%d",&nStudents,&nInstructs)) {
//        for(int i=1; i<=nStudents; i++)
//            scanf("%d",&arr[i]);
        buildTree(1,1,nStudents);
        //puts("..");
        char ch;
        int i,j;
        while(nInstructs--) {
            scanf("%c %d%d",&ch,&i,&j);
            getchar();
           // printf("ch = %c i = %d j = %d\n",ch,i,j);
            if(ch == 'Q') printf("%d\n",query(1,i,j));
            if(ch == 'U') update(1,i,j);
        }
    }
    return 0;
}
