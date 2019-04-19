#include <bits/stdc++.h>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

class Euler {
private:
    static const int MAXN = 3000000 + 16;
    int euler[MAXN];
public:
    Euler() {
        memset(euler, 0, sizeof(euler));
        euler[1] = 1;
        for(int i = 2; i < MAXN; i++) if(!euler[i]) {
            for(int j = i; j < MAXN; j += i) {
                if(!euler[j]) euler[j] = j;
                euler[j] = euler[j] / i * (i - 1);
            }
        }
    }
    int operator [] (int i) const {
        return euler[i];
    }
    long long eular(long long n) {
        long long ans = n;
        for(int i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                ans -= ans / i;
                while(n % i == 0) n /= i;
            }
        }
        if(n > 1) ans -= ans / n;
        return ans;
    }
    vector<int>::size_type size() const {
        return MAXN;
    }
} EULER;

class PrimeSiever {
private:
    static const int MAXN = 100000 + 16;
    bool isPrime[MAXN];
    vector<int> primes;
public:
    PrimeSiever() {
        memset(isPrime, true, sizeof(isPrime));
        primes.clear();
        isPrime[0] = isPrime[1] = false;
        for(long long i = 2; i < MAXN; ++i) if(isPrime[i]) {
                primes.push_back(i);
                for(long long j = i * i; j < MAXN; j += i)
                    isPrime[j] = false;
            }
    }
    vector<int>::size_type size() const {
        return primes.size();
    }
    int operator [] (int i) const {
        return primes[i];
    }
    bool prime(int x) const {
        return isPrime[x];
    }
    // [(prime, cnt)]
    vector<pair<int, int> > getFactors(int x) {
        assert(x != 0);
        vector<pair<int, int> > result;
        int temp = x;
        for(int i = 0; primes[i] <= x / primes[i]; ++i) {
            if(temp % primes[i] == 0) {
                pair<int, int> ans = make_pair(primes[i], 0);
                while(temp % primes[i] == 0) {
                    ++ans.second;
                    temp /= primes[i];
                }
                result.push_back(ans);
            }
        }
        if(temp != 1) result.push_back(make_pair(temp, 1));
        return result;
    }
} PS;

int main(int argc, char **argv) {

    return 0;
}
