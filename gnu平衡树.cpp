#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define DBG(x) cerr << #x << " = " << x << endl
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> MultiSet;
//rb_tree_tag splay_tree_tag ov_tree_tag
const int INF = 0x7F7F7F7F;

//order从0开始数，order_of_key(x)返回比x小的有多少个

int main(int argc, char **argv) {
    Set st;
    st.insert(1);
    st.insert(1);
    st.insert(1);
    st.erase(1);
    auto it = st.lower_bound(1);
    st.erase(it);
    for(Set::iterator it = st.begin(); it != st.end(); ++it) {
        cout << *it << endl;
    }

    st.insert(1);
    st.insert(2);
    st.insert(3);
    st.insert(4);

    assert(st.order_of_key(1) == 0);
    assert(st.order_of_key(2) == 1);
    assert(st.order_of_key(3) == 2);
    assert(st.order_of_key(4) == 3);
    assert(st.order_of_key(-13) == 0);
    assert(st.order_of_key(777) == 4);


    assert(*st.find_by_order(-123) == 0);	// NULL ?
    assert(*st.find_by_order(0) == 1);
    assert(*st.find_by_order(1) == 2);
    assert(*st.find_by_order(2) == 3);
    assert(*st.find_by_order(3) == 4);
    assert(*st.find_by_order(123) == 0);	// NULL ?


    st.erase(-123);
    cout << st.size() << endl;

    st.erase(1);
    cout << st.size() << endl;

    MultiSet mst;
    int tot = 0;
    mst.insert({1, tot++});
    mst.insert({1, tot++});
    mst.insert({1, tot++});
    DBG(mst.size());
    mst.erase(mst.lower_bound({1, 0}));
    DBG(mst.size());
    DBG(mst.order_of_key({1, 0}));  //比1小的有多少个，即为1的order，从0开始数
    DBG(mst.order_of_key({1, INF})); //比1小的个数+1的个数
    return 0;
}
