#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

template<typename T>
T LCM(const vector<T> &vec) {
    return accumulate(vec.begin(), vec.end(), T(1), [](T x, T y) -> T {return x * y / __gcd(x, y);});
}
template<typename T>
T GCD(const vector<T> &vec) {
    return accumulate(vec.begin(), vec.end(), T(1), [](T x, T y) -> T {return __gcd(x, y);});
}


int main(int argc, char **argv) {
    vector<LL> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << LCM(vec) << endl;
    cout << GCD(vec) << endl;
    return 0;
}
