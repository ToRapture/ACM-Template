#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

int a[10000];

int main(int argc, char **argv) {
    int n, x, p;
    while(cin >> n >> x) {
        memset(a, false, sizeof(a));
        for(int i = 1; i <= x; ++i) a[i] = true;
        int left = 1;
        int right = n;
        while(left <= right) {   //最大值尽量小， 可行值尽量小
             int mid = left + (right - left) / 2;
             if(!a[mid]) {  //if check is ok
                right = mid - 1;
             } else {
                left = mid + 1;
             }
         }
         DBG(left);
    }
    return 0;
}
