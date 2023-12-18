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
    // Base case: if we ran out of piles, or we're out of capacity, we can't get any more
    if (pile >= n || k <= 0) return 0;
    if (dp[pile][k] != -1) return dp[pile][k]; // you know what this does

    // Try taking different numbers from the pile, from min(12, k) down to 0
    // I don't know why I did this in reverse, there would literally be no difference if I iterated forward
    ll max = 0;
    rev(i, min(12, k), -1) {
        // Try taking this number: transition to the next index, with new capacity k-(the number we took)
        max = ::max(max, pfx[pile][i] + find_max(dp, pfx, n, pile + 1, k - i));
    }

    return dp[pile][k] = max;
}

int main() {
    int n, k;
    cin >> n >> k;

    vec<vec<ll>> dp(n, vec<ll>(k + 1, -1)); // dp table
    vec<vec<int>> pfx(n, vec<int>(13, 0)); // prefix sum for each pile

    // Build prefix sum for each pile of 12
    rep(i, 0, n) {
        rep(j, 0, 12) {
            int tmp;
            cin >> tmp;

            pfx[i][j + 1] = pfx[i][j] + tmp;
        }
    }

    // Run dp
    ll max = find_max(dp, pfx, n, 0, k);
    cout << max;

    return 0;
}
