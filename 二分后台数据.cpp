#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

int target = 36;

int main(int argc, char **argv) {
    while(cin >> target) {
        int L = 0, R = 100000000;
        while(L < R) {
            int mid = L + R >> 1;
            if(mid >= target) {
                R = mid;
            } else L = mid + 1;
        }
        DBG((L == target));
    }
    return 0;
}
