#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n, m = 0;
    cin >> n;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
        m = max(m, a[i]);
    }

    set<int> s(all(a));
    int mex = 0;
    for (; mex <= m; mex++)
        if (!s.count(mex)) break;

    vector<pair<int, int>> res;
    set<int> c;
    int l = 0;
    rep(i, 0, n) {
        if (a[i] < mex) c.insert(a[i]);
        if (c.size() == mex) {
            res.emplace_back(l + 1, i + 1);
            c.clear(), l = i + 1;
        }
    }
    if (res.size() <= 1) return void(cout << "-1\n");
    res.back().second = max(res.back().second, n);

    cout << res.size() << "\n";
    for (auto [a, b] : res) {
        cout << a << " " << b << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
