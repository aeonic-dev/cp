#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

ll min_dif(vec<int> &s, int i = 0, ll dif = 0) {
    if (i >= s.size()) return abs(dif);
    return min(
            min_dif(s, i + 1, dif + s[i]),
            min_dif(s, i + 1, dif - s[i])
    );
}

void solve() {
    int n;
    cin >> n;
    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];

    ll res = min_dif(s);
    cout << res << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
