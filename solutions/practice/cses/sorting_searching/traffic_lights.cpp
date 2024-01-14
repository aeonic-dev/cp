#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int x, n, cur;
    cin >> x >> n;

    set<int> l{0, x};
    multiset<int> s{x};
    rep(i, 0, n) {
        cin >> cur;
        auto hi = l.upper_bound(cur);
        auto lo = hi;
        lo--;

        s.erase(s.find(*hi - *lo));
        s.insert(*hi - cur), s.insert(cur - *lo);
        l.insert(cur);

        cout << *s.rbegin() << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
