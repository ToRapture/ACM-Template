struct BIT {
    static const int MAXN = 50000 + 16;
    typedef int TP;

    static int lowbit(int x) {
        return x & -x;
    }
    int n;
    TP C[MAXN];
    void init(int n) {
        this->n = n;
        memset(C, 0, sizeof(C));
    }
    void add(int x, TP d) {
        while(x <= n) {
            C[x] += d;
            x += lowbit(x);
        }
    }
    TP sum(int x) { // [1, x]
        TP res = 0;
        while(x > 0) {
            res += C[x];
            x -= lowbit(x);
        }
        return res;
    }
    TP sum(int l, int r) {  // [l, r]
        return sum(r) - sum(l - 1);
    }
} bit;
