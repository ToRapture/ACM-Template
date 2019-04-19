// hdu 4970
#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

struct Fucker {
    static const int maxn = 100000 + 16;
    typedef LL typev;
    typev a[maxn], sum[maxn];
    int n;
    void init(int n) {
        this->n = n;
        for(int i = 0; i <= n; ++i) a[i] = 0;
    }
    void add(int l, int r, typev num) {
        a[l] += num;
        a[r + 1] -= num;
    }
    void build() {
        typev tmp = 0;
        for(int i = 1; i <= n; ++i) {
            a[i] += tmp;
            tmp = a[i];
        }
        for(int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + a[i];
    }
    typev get(int x) {	//[1, x]
        return sum[x];
    }
    typev get(int l, int r) {	//[l, r]
        return get(r) - get(l - 1);
    }
} fucker;

int main(int argc, char **argv) {
    int n;
    while(~scanf("%d", &n), n) {
        fucker.init(n);
        int Q;
        scanf("%d", &Q);
        while(Q--) {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);
            fucker.add(l, r, d);
        }
        fucker.build();
        int ans = 0;
        scanf("%d", &Q);
        while(Q--) {
            LL hp;
            int x;
            scanf("%lld%d", &hp, &x);
            if(hp > fucker.get(x, n)) ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
