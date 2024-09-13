#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

const ll base = 1e11 + 3;
vec<ll> pw;

ll get_hash(string &s) {
    ll res = 0;
    for (auto ch : s) {
        res *= base;
        res += ch - 'b';
    }
    return res;
}

void solve() {
    string a, b;
    cin >> a >> b;

    if (a.size() == b.size() && a != b) {
        cout << "0\n";
        return;
    }

    pw = vec<ll>(a.size(), 1);
    rep(i, 1, a.size()) pw[i] = pw[i - 1] * base;

    vec<ll> pfx(a.size() + 1, 0);
    rep(i, 0, a.size()) {
        pfx[i + 1] = pfx[i] * base + (a[i] - 'b');
    }

    ll hash = get_hash(b);
    int num = 0;
    rep(i, b.size(), a.size() + 1) {
        ll cmp = pfx[i] - (pfx[i - b.size()] * pw[b.size()]);
        if (hash == cmp) num++;
    }

    cout << num << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
