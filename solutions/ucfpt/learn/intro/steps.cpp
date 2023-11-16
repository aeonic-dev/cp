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
    int n;
    cin >> n;
    vec<vec<int>> adj(n, vec<int>(n, INT_MAX));
    rep(i, 0, n) {
        rep(j, 0, n) {
            cin >> adj[i][j];
        }
    }

    int t;
    cin >> t;
    rep(i, 0, t) {
        string s;
        cin >> s;

        ll steps = 0;
        rep(j, 1, s.size()) steps += adj[s[j - 1] - 'A'][s[j] - 'A'];
        cout << steps << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
