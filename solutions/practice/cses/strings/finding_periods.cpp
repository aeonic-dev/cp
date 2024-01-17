#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;

const ll base = 1e11 + 3;

void solve() {
    string s;
    cin >> s;

    vec<ll> pwr(s.size() + 1, 1),
            pfx(s.size() + 1, 0);
    rep(i, 0, s.size()) {
        pwr[i + 1] = pwr[i] * base;
        pfx[i + 1] = pfx[i] * base + (s[i] - 'a' + 1);
    }

    rep(len, 1, s.size()) {
        ll hash = 0;
        int l = s.size(); // # left
        while (l) {
            int lu = min(len, l);
            hash *= pwr[lu];
            hash += pfx[lu];
            l -= lu;
        }

        if (hash == pfx[s.size()]) cout << len << " ";
    }
    cout << s.size();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
