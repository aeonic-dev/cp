#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vec<int> w(n), a(m);
    rep(i, 0, n) cin >> w[i];
    rep(i, 0, m) cin >> a[i];
    sort(all(w)), sort(all(a));

    int num = 0, p = 0;
    rep(i, 0, m) {
        if (p >= n) break;
        int apt = a[i], x = w[p];
        if (apt < x - k) continue;

        if (apt <= x + k) num++;
        else i--;
        p++;
    }

    cout << num << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
