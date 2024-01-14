#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, m;
    cin >> n >> m;

    multiset<int, greater<int>> t;
    rep(i, 0, n) {
        int p;
        cin >> p, t.insert(p);
    }

    rep(i, 0, m) {
        int mp;
        cin >> mp;
        auto it = t.lower_bound(mp);
        if (it == t.end()) {
            cout << "-1\n";
            continue;
        }

        cout << *it << "\n";
        t.erase(it);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
