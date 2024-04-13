#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

vi cs{15, 10, 6, 3, 1};
void solve() {
    int n;
    cin >> n;

    int res = INT_MAX;
    rep(b, 0, 3) {
        rep(c, 0, 5) {
            rep(d, 0, 2) {
                rep(e, 0, 3) {
                    int n2 = n - b * 10 - c * 6 - d * 3 - e;
                    if (n2 < 0 || n2 % 15) continue;
                    res = min(res, n2 / 15 + b + c + d + e);
                }
            }
        }
    }
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
