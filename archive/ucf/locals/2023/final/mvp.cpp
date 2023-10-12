#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long int li;
typedef long double ld;

#define vec vector
#define pb push_back
#define eb emplace_back
#define rep(i, s, e) for (int i = s; i < e; i++)
#define rev(i, s, e) for (int i = s; i > e; i--)
#define trav(x, s) for (auto &x : s)

ll find_max(vec<vec<ll>> &dp, vec<vec<int>> &pfx, int n, int pile, int k) { // pile = next pile, k = # left to eat
    if (pile >= n || k <= 0) return 0;
    if (dp[pile][k] != -1) return dp[pile][k];

    ll max = 0;
    rev(i, min(12, k), -1) {
        max = ::max(max, pfx[pile][i] + find_max(dp, pfx, n, pile + 1, k - i));
    }

    return dp[pile][k] = max;
}

int main() {
    int n, k;
    cin >> n >> k;

    vec<vec<ll>> dp(n, vec<ll>(k + 1, -1));
    vec<vec<int>> pfx(n, vec<int>(13, 0));
    rep(i, 0, n) {
        rep(j, 0, 12) {
            int tmp;
            cin >> tmp;

            pfx[i][j + 1] = pfx[i][j] + tmp;
        }
    }

    ll max = find_max(dp, pfx, n, 0, k);

    cout << max;

    return 0;
}