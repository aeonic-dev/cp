#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

void solve() {
    int maxn, num, sum;
    cin >> maxn >> num;
    vi res;
    rep(n, 2, maxn + 1) {
        cin >> sum;
        if (sz(res) == num) continue; // keep reading input, but we're done
        int should_be = n * (num - sz(res));
        for (int x : res) should_be += n % x;
        int dif = should_be - sum;
        rep(i, 0, dif / n) res.push_back(n);
    }
    cout << num << " ";
    for (int x: res) cout << x << " ";
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
