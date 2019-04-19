//hdu 1686 KMP模板题
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); ++i)
#define Rep(i,n) for(int i=1; i<=(n); ++i)
#define mt(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pb push_back
#define sqr(x) ((x)*(x))
#define OUT(x) cout << #x << " = " << x << endl
using namespace std;
typedef long long LL;

const int M = 10024;
const int N = 1000000 + 1024;
char x[M], y[N];
int Next[M];

void getNext(const char x[], int m, int kmpNext[]) {
    int i, j;
    i = 0, j = kmpNext[0] = -1;
    while(i < m) {
        while(~j && x[i] != x[j]) j = kmpNext[j];
        if(x[++i] == x[++j]) kmpNext[i] = kmpNext[j];
        else kmpNext[i] = j;
    }
}
int KMP(const char x[], int m, const char y[], int n) {
    int i, j;
    int ans = 0;
    getNext(x, m, Next);
    i = j = 0;
    while(i < n) {
        while(~j && y[i] != x[j]) j = Next[j];
        ++i, ++j;
        if(j >= m) {
            ++ans;
            //cout << "matched at " << i - j + 1 << endl;
            j = Next[j];
        }
    }
    return ans;
}



int main(int argc, char **argv) {
    int T;
    cin >> T;
    while(T--) {
        cin >> x >> y;
        int m = strlen(x);
        int n = strlen(y);
        cout << KMP(x, m, y, n) << endl;
    }
	return 0;
}

/*
3
BAPC
BAPC
AZA
AZAZAZA
VERDI
AVERDXIVYERDIAN

*/
