#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int N = 1024;

int pref[N][N], order[N][N], nxt[N];
int future_husband[N], future_wife[N];

queue<int> Q;

void engage(int man, int woman) {
    int m = future_husband[woman];
    if(m) {
        future_wife[m] = 0;
        Q.push(m);
    }
    future_wife[man] = woman;
    future_husband[woman] = man;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        while(!Q.empty()) Q.pop();
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j)
                scanf("%d", &pref[i][j]);
            nxt[i] = 1;
            future_wife[i] = 0;
            Q.push(i);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                int x;
                scanf("%d", &x);
                order[i][x] = j;
            }
            future_husband[i] = 0;
        }
        while(!Q.empty()) {
            int man = Q.front(); Q.pop();
            int woman = pref[man][nxt[man]++];
            if(!future_husband[woman] || order[woman][man] < order[woman][future_husband[woman]])
                engage(man, woman);
            else Q.push(man);
        }
        for(int i = 1; i <= n; ++i)
            printf("%d\n", future_wife[i]);
        if(T) puts("");
    }
    return 0;
}

/**
1
5
1 2 3 5 4
5 2 4 3 1
3 5 1 2 4
3 4 2 1 5
4 5 1 2 3
2 5 4 1 3
3 2 4 1 5
1 2 4 3 5
4 1 2 5 3
5 3 2 4 1

*/

/**
1
2
5
3
4
*/