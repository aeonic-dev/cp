#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, k;
    cin >> n;

    multiset<int> s;
    rep(i, 0, n) {
        cin >> k;
        auto it = s.upper_bound(k);
        if (it == s.end()) {
            s.insert(k);
            continue;
        }

        int old = *it;
        s.erase(it), s.insert(k);
    }

    cout << s.size() << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
