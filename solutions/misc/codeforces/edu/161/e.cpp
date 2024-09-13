#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    ll x;
    cin >> x;

    int xl2 = (int) log2(x), n = xl2;
    ll num = (1ll << xl2), l;
    while (l = x - num, l > 0) {
        if (n > 200) return void(cout << "-1\n");
        int ll2 = (int) log2(l);
        n++, num += (1ll << ll2);
    }

    cout << n << "\n";
    rep(i, 0, xl2) cout << i << " ";

    num = (1 << xl2);
    while (l = x - num, l > 0) {
        int ll2 = (int) log2(l);
        cout << ll2 << " ";
        num += (1ll << ll2);
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
