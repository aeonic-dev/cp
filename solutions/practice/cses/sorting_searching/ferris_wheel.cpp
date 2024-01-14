#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, x;
    cin >> n >> x;
    vec<int> p(n);
    rep(i, 0, n) cin >> p[i];
    sort(p.rbegin(), p.rend());

    multiset<int, greater<int>> s;
    int filled = 0;
    rep(i, 0, n) {
        int num = p[i], dif = x - num;
        auto it = s.lower_bound(dif);
        if (it == s.end()) {
            s.insert(num);
            continue;
        }

        int old = *it;
        s.erase(it);
        filled++;
    }

    cout << s.size() + filled;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
