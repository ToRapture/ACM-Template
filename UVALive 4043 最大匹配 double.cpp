#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const int maxn = 100 + 10;
const double eps = 1e-10;

int n, link[maxn];
double w[maxn][maxn], Lx[maxn], Ly[maxn];
bool S[maxn], T[maxn];

bool match(int i) {
    S[i] = true;
    for(int j = 1; j <= n; ++j) if(fabs(Lx[i] + Ly[j] - w[i][j]) < eps && !T[j]){
        T[j] = true;
        if(link[j] == -1 || match(link[j])){
            link[j] = i;
            return true;
        }
    }
    return false;
}

void update() {
    double a = 1 << 30;
    for(int i = 1; i <= n; ++i) if(S[i])
        for(int j = 1; j <= n; ++j) if(!T[j])
            a = min(a, Lx[i] + Ly[j] - w[i][j]);
    for(int i = 1; i <= n; ++i) {
        if(S[i]) Lx[i] -= a;
        if(T[i]) Ly[i] += a;
    }
}

void KM() {
    for(int i = 1; i <= n; i++) link[i] = -1;
    for(int i = 1; i <= n; ++i) Lx[i] = Ly[i] = 0.00;
    for(int i = 1; i <= n; i++) {
        while(true) {
            for(int j = 1; j <= n; j++) S[j] = T[j] = false;
            if(match(i)) break;
            else update();
        }
    }
}

vector<pair<int, int> > pw, pb;

double dist(int x, int y) {
    return sqrt((pb[x].first - pw[y].first) * (pb[x].first - pw[y].first) + (pb[x].second - pw[y].second) * (pb[x].second - pw[y].second));
}

int main(int argc, char **argv) {
    while(~scanf("%d", &n)) {

        pw.resize(n);
        pb.resize(n);
        for(int i = 0; i < n; ++i) scanf("%d%d", &pw[i].first, &pw[i].second);
        for(int i = 0; i < n; ++i) scanf("%d%d", &pb[i].first, &pb[i].second);

        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
                w[i + 1][j + 1] = -dist(i, j);
            }

        KM();
        for(int i = 1; i <= n; ++i) printf("%d\n", link[i]);
    }
    return 0;
}

/**
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -60

*/

/**
4
2
1
5
3
*/