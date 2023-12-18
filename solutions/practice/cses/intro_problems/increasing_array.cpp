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
    int n, last = -1;
    cin >> n;
    vec<int> x(n);
    ll m = 0;
    rep(i, 0, n) {
        cin >> x[i];
        if (last != -1 && x[i] < last) {
            m += last - x[i];
            x[i] = last;
        }

        last = x[i];
    }
    cout << m << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
