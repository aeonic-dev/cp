#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
    ll r, c;
    cin >> r >> c;
    ll m = max(r, c);
    ll sq1 = m * m;
    ll sq2 = (m - 1) * (m - 1);
    if (m % 2 == 0) cout << (c <= r ? sq1 + 1 - c : sq2 + r);
    else cout << (c > r ? sq1 + 1 - r : sq2 + c);
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
