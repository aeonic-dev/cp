#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

typedef bitset<200001> bs;

void solve() {
    int n;
    cin >> n;
    bs a, b;
    {
        string astr, bstr;
        cin >> astr >> bstr;
        rep(i, 0, n) a[i] = (astr[i] == '1');
        rep(i, 0, n) b[i] = (bstr[i] == '1');
    }

    bs path;
    path[0] = a[0];
    path[n] = b[n - 1];

    int af = 1, bf = 1;
    rep(i, 0, n - 1) {
        if (a[i + 1] xor b[i]) {
            // disqualify whichever is nonzero
            (a[i + 1] ? af : bf) = 0;
        }
        path[i + 1] = af ? a[i + 1] : b[i];
    }

    vector<vll> dp(2, vll(n, -1));
    auto go = [&](int i, int j, auto &go) -> ll {
        if (j == n) return i;

        auto &res = dp[i][j];
        if (res != -1) return res;

        bs &s = i ? b : a;
        if (s[j] != path[i + j])
            return res = 0;

        res = go(i, j + 1, go);
        if (i == 0) res += go(1, j, go);
        return res;
    };
    ll res = go(0, 0, go);

    rep(i, 0, n + 1) cout << path[i];
    cout << "\n" << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
