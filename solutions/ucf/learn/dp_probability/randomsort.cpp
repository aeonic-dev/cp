#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    array<int, 8> a;
    rep(i, 0, n) cin >> a[i];

    map<array<int, 8>, ld> dp;
    auto go = [&](array<int, 8> arr, auto &&go) -> ld {
        rep(i, 0, n) if (arr[i] != i + 1) goto sad;
        return 0;
    sad:;
        if (dp.count(arr)) return dp[arr];

        ld &res = dp[arr] = 0;
        int pos_swaps = 0; // # of possible swaps
        rep(i, 0, n) {
            rep(j, i + 1, n) {
                if (arr[i] < arr[j]) continue;

                swap(arr[i], arr[j]);
                res += 1 + go(arr, go), pos_swaps++;
                swap(arr[i], arr[j]);
            }
        }
        res /= pos_swaps;
        return res;
    };
    ld res = go(a, go);
    cout << fixed << setprecision(4) << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
