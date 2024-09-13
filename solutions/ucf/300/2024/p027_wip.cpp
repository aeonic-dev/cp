#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n4, n6, n8, n12, n20;
    cin >> n4 >> n6 >> n8 >> n12 >> n20;
    map<int, ll> d4, d6, d8, d12, d20;

    // this part needs to be a DP I think, this is way too slow
    auto go = [&](int sides, int n, int i, ll sum, map<int, ll>& mp, auto &go) {
        if (i == n) {
            mp[sum]++;
            return;
        }
        for (int j = 1; j <= sides; j++) {
            go(sides, n, i + 1, sum + j, mp, go);
        }
    };

    // god is dead
    vector<map<int, ll>> maps;
    if (n4) go(4, n4, 0, 0, d4, go), maps.push_back(d4);
    if (n6) go(6, n6, 0, 0, d6, go), maps.push_back(d6);
    if (n8) go(8, n8, 0, 0, d8, go), maps.push_back(d8);
    if (n12) go(12, n12, 0, 0, d12, go), maps.push_back(d12);
    if (n20) go(20, n20, 0, 0, d20, go), maps.push_back(d20);

    map<int, ll> ans;
    auto go2 = [&](int i, ll sum, ll fr, auto &go2) {
        if (i == sz(maps)) {
            ans[sum]++;
            return;
        }
        for (auto [roll, freq] : maps[i]) {
            go2(i + 1, sum + roll, fr * freq, go2);
        }
    };
    go2(0, 0, 1, go2);
    vector<pair<int, ll>> res;
    for (auto [r, f] : ans) res.emplace_back(f, r);
    sort(rbegin(res), rend(res));
    for (auto [_, r] : res) cout << r << " ";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
