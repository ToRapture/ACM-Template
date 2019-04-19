// hdu 1724
#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const double eps = 1e-7;
double PI = 3.141592653589793;

double a, b, l, r;

inline double F(double x) {
    return sqrt(b * b * (1 - x * x / a / a));
}

double simpson(double a, double b) {
    double c = a + (b - a) / 2;
    return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A) {
    double c = a + (b - a) / 2;
    double L = simpson(a, c), R = simpson(c, b);
    if(fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
    return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

double asr(double a, double b, double eps) {
    return asr(a, b, eps, simpson(a, b));
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%lf%lf%lf%lf", &a, &b, &l, &r);
        printf("%.3f\n", 2 * asr(l, r, eps));
    }
    return 0;
}

/**
2
2 1 -2 2
2 1 0 2

*/

/**
6.283
3.142
*/
