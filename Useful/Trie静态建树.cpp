//hdu 1251
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

const int M = 10000 + 1024 * 3;


struct Trie {
    int next[M * 30][30], cnt[M * 30];
    int tot, root;
    int newNode() {
        memset(next[tot], -1, sizeof(next[tot]));
        return tot++;
    }
    void init() {
        tot = 0;
        memset(cnt, 0, sizeof(cnt));
        root = newNode();
    }
    void insert(const char *buf) {
        int p = root;
        for(int i = 0; buf[i]; ++i) {
            int id = buf[i] - 'a';
            if(next[p][id] == -1) next[p][id] = newNode();
            p = next[p][id];
            ++cnt[p];
        }
    }
    int query(const char *buf) {          //查询以buf[]为前缀的字符串的个数， 包括buf[]
        int p = root;
        for(int i = 0; buf[i]; ++i) {
            int id = buf[i] - 'a';
            if(~next[p][id]) p = next[p][id];
            else return 0;
        }
        return cnt[p];
    }
} trie;

char buf[5000];

int main(int argc, char **argv) {
    trie.init();
    while(gets(buf)) {
        if(buf[0] == 0) break;
        trie.insert(buf);
    }
    while(gets(buf)) {
        printf("%d\n", trie.query(buf));
    }
    return 0;
}
/*
banana
band
bee
absolute
acm

ba
b
band
abc

*/
