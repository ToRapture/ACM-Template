#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

int arr[50005];
int cam[50005];
int nCams;
int lowbit(int t) {
    //return t & ( t ^ ( t - 1 ) );
    return t & (-t);
}
int getSum(int x) {
    int sum = 0;
    while(x > 0) {
        sum += arr[x];
        x -= lowbit(x);
    }
    return sum;
}
int query(int i,int j) {
    return getSum(j) - getSum(i-1);
}
void add(int n, int num) {
    while(n <= nCams) {
        arr[n] += num;
        n += lowbit(n);
    }
}

int main() {
    int nCases;
    scanf("%d",&nCases);
    for(int cnt=1; cnt<=nCases; cnt++) {
        printf("Case %d:\n",cnt);
        scanf("%d",&nCams);
        memset(arr,0,sizeof(arr));
        for(int i=1; i<=nCams; i++) {
            int t;
            scanf("%d",&t);
            add(i,t);
        }
        char s[5];
        while(1) {
            scanf("%s",s);
            if(s[0] == 'E') break;
            if(s[0] == 'Q') {
                int i,j;
                scanf("%d%d",&i,&j);
                printf("%d\n",query(i,j));
            }
            if(s[0] == 'A') {
                int i,j;
                scanf("%d%d",&i,&j);
                add(i,j);
            }
            if(s[0] == 'S') {
                int i,j;
                scanf("%d%d",&i,&j);
                add(i,-j);
            }
        }
    }
    return 0;
}
