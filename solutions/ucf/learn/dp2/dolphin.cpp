#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

int tc = 0;
void solve() {
    int n;
    cin >> n;
    vi a(n), srt;
    for (int &x : a) cin >> x;

    map<int, int> comp;
    srt = a, sort(all(srt));
    for (int x : srt)
        if (!comp.count(x)) comp[x] = sz(comp);
    for (int &x : a) x = comp[x];

    vector<vector<vi>> dp(2, vector(sz(comp), vi(n, -1)));
    function<int(int, int, bool)> go = [&](int i, int last, bool dec) -> int {
        if (i == n) return 0;

        int &res = dp[dec][last][i], x = a[i];
        if (res != -1) return res;

        res = go(i + 1, last, dec);

        if (!dec && x >= last)
            res = max({res,
                       1 + go(i + 1, x, 0),
                       1 + go(i + 1, x, 1)});

        if (dec && x <= last)
            res = max(res,
                      1 + go(i + 1, x, 1));
        return res;
    };
    int res = go(0, 0, 0);
    cout << "Case " << ++tc << ": Dynamo ate " << res << " food pellet(s).\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
