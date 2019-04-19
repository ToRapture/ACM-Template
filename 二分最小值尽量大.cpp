#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;


bool fuck[2048];

bool test(int x) {
    return !fuck[x];
}

int main(int argc, char **argv) {
    int n, m;
    while(cin >> n >> m) {
        int L = 1, R = n;
        memset(fuck, false, sizeof(fuck));
        for(int i = m; i <= n; ++i) fuck[i] = true;
        while(L < R) {  //最小值尽量大
            int M = L + (R - L + 1) / 2;
            if(test(M)) L = M;
            else R = M - 1;
        }
        DBG(L);
    }
    return 0;
}
