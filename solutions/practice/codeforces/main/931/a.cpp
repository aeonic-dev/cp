#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    vi s(n);
    rep(i, 0, n) cin >> s[i];
    sort(all(s));

    int a = s[0], b = s[1], c = s[n - 2], d = s[n - 1];
    ll res = abs(c - a) + abs(c - b) + abs(d - b) + abs(d - a);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
