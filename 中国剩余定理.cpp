// hdu 5446

#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 100000 + 16;

LL fac[N], a[16], pr[16];

void init(LL p) {
    fac[0] = 1LL;
    for(LL i = 1LL; i <= p; ++i)
        fac[i] = (fac[i - 1] * i) % p;
}

LL extend_gcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        LL res = extend_gcd(b, a % b, y, x);
        y -= a / b * x;
        return res;
    }
}


LL Mul(LL x, LL n, LL mod) {
    LL res = 0;
    while(n) {
        if(n & 1) res = (res + x) % mod;
        x = (x << 1) % mod;
        n >>= 1;
    }
    return res;
}

LL Pow(LL x, LL n, LL mod) {
    LL res = 1;
    while(n) {
        if(n & 1) res = Mul(res, x, mod);
        x = Mul(x, x, mod);
        n >>= 1;
    }
    return res;
}

LL lucas(LL a, LL k, LL p) { // 求C(n, m) % p, p为素数, p最大约为10^7. a, b可以很大.
    LL res = 1;
    while(a && k) {
        LL aa = a % p, bb = k % p;
        if(aa < bb) return 0;
        res = (res * fac[aa] * Pow(fac[bb] * fac[aa - bb] % p, p - 2, p)) % p;
        a /= p;
        k /= p;
    }
    return res;
}

LL CRT(LL a[], LL p[], int k) {
    LL mod = 1;
    LL res = 0;
    for(int i = 0; i < k; ++i) mod *= p[i];
    for(int i = 0; i < k; ++i)  {
        LL Mi = mod / p[i];
        LL x, y;
//        extend_gcd(Mi, p[i], x, y); // x = Mi mod p[i]下的逆元.
        x = Pow(Mi, p[i] - 2, p[i]);
        res = (res + Mul(Mul(x, Mi, mod), a[i], mod)) % mod; // res = (res + x * Mi * a[i]) % mod.
    }
    return (res + mod) % mod;
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--) {
        LL n, m;
        int k;
        cin >> n >> m >> k;
        for(int i = 0; i < k; ++i) {
            cin >> pr[i];
            init(pr[i]);
            a[i] = lucas(n, m, pr[i]);
        }
        cout << CRT(a, pr, k) << endl;
    }
    return 0;
}

/**
1
9 5 2
3 5

6
*/
