#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

vi dp;
int go(int n) {
    if (n == 0) return 0;
    if (n <= 0) return 1e7;
    if (n <= 9) return 1;

    auto &res = dp[n];
    if (res != -1) return res;

    res = 1e7;
    for (char d : to_string(n)) {
        res = min(res, 1 + go(n - (d - '0')));
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    dp = vi(n + 1, -1);
    int res = go(n);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
