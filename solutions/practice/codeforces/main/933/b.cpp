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
    vi a(n);
    rep(i, 0, n) cin >> a[i];

    rep(i, 0, n - 2) {
        int d = a[i];
        if (d == 0) continue;
        if (d < 0) return void(cout << "no\n");

        a[i] -= d, a[i + 2] -= d;
        a[i + 1] -= d * 2;
    }
    rep(i, 0, n) {
        if (a[i] != 0) return void(cout << "no\n");
    }
    cout << "yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
