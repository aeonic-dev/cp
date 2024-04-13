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
    vi a(n), pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> a[i];
    }
    sort(all(a));
    rep(i, 0, n)pfx[i + 1] = pfx[i] + a[i];

    int min = INT_MAX;
    rep(i, 0, n + 1) {
        rep(j, i + 1, n + 1) {
            int sum = pfx[j] - pfx[i];
            min = ::min(min, sum);
        }
    }
    if (min >= 0) return void(cout << pfx[n] << "\n");
    cout << pfx[n] - (min * 2) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
