#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    string str;
    cin >> str;

    int n = sz(str), m = n / 2;
    string a = str.substr(0, m), b = str.substr(m + n % 2);
    reverse(all(b));

    vector<bool> match(m);
    rep(i, 0, m) match[i] = (a[i] == b[i]);

    // {first i are correct; whether current was flipped}
    vector<vector<int>> dp(m, vector<int>(2, INT_MAX));

    // f = whether match[i] has been flipped
    auto go = [&](int i, bool f, const auto &go) -> int {
        if (i == m) return 0;

        int &res = dp[i][f];
        if (res != INT_MAX) return res;

        if (match[i]) {
            if (f) // ...0,
                res = min(1 + go(i + 1, 1, go),
                          1 + go(i, 0, go));
            else // ...1,
                res = min(go(i + 1, 0, go),
                          2 + go(i + 1, 1, go));
        } else {
            if (f) // ...1,
                res = min(go(i + 1, 0, go),
                          1 + go(i + 1, 1, go));
            else // ...0,
                res = min(1 + go(i + 1, 1, go),
                          2 + go(i + 1, 0, go));
        }

        return res;
    };
    int res = go(0, 0, go);
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
