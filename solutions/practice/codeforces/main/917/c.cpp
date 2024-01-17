#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;
typedef vec<int> vi;

// start = (start % k), d = ind - (start % k)
typedef map<tuple<int, int>, ll> DP;
ll after_first(int n, int k, int d, DP &dp, vi &v, vi &add, int start, int ind = 0) {
    if (ind >= d) return 0;

    auto key = make_tuple(start % k, ind - (start % k));
    if (!dp.count(key)) dp[key] = -1;
    ll &res = dp[key];
    if (res != -1) return res;

    int b = v[ind % k];
    add[0]++, add[b]--;
    res = after_first(n, k, d, dp, v, add, start, ind + 1);
    add[0]--, add[b]++;

    ll num = 0;
    vec<ll> pfx(n + 1, 0);
    rep(i, 0, n) {
        pfx[i + 1] = pfx[i] + add[i];
        int val = pfx[i + 1];
        if (val == i + 1) num++;
    }

    vi add2(n + 1, 0);
    res = max(res, num + after_first(n, k, d, dp, v, add2, ind, ind + 1));
    return res;
}

ll max_score(int n, int k, int d, DP &dp, vi &a, vi &v, vi &add, vi &pfx, int ind = 0) {
    if (ind >= d) return 0;
    int b = v[ind % k];

    add[0]++, add[b]--;
    ll res = max_score(n, k, d, dp, a, v, add, pfx, ind + 1);
    add[0]--, add[b]++;

    ll num = 0;
    pfx[0] = 0;
    rep(i, 0, n) {
        pfx[i + 1] = pfx[i] + add[i];
        int val = pfx[i + 1] + a[i];
        if (val == i + 1) num++;
    }

    vi add2(n + 1, 0);
    res = max(res, num + after_first(n, k, d, dp, v, add2, ind, ind + 1));
    return res;
}

void solve() {
    int n, k, d;
    cin >> n >> k >> d;

    vi a(n), v(k), add(n + 1, 0), pfx(n + 1);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, k) cin >> v[i];

    DP dp;
    ll res = max_score(n, k, d, dp, a, v, add, pfx);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
