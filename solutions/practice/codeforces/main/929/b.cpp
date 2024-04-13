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
    vi a(n), f(3, 0);
    ll sum = 0;
    rep(i, 0, n) {
        cin >> a[i];
        f[a[i] % 3]++;
        sum += a[i];
    }

    if (sum % 3 == 0) return void(cout << "0\n");
    if (f[sum % 3] || sum % 3 == 2) return void(cout << "1\n");
    cout << "2\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
