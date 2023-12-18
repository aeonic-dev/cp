#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, a, b;
    cin >> n;
    vec<pair<int, int>> e;
    e.reserve(n * 2);
    rep(i, 0, n) {
        cin >> a >> b;
        e.emplace_back(a, 1);
        e.emplace_back(b, -1);
    }
    sort(all(e));
    int max = 0, num = 0;
    for (auto evt : e) {
        num += evt.second;
        max = ::max(max, num);
    }
    cout << max << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
