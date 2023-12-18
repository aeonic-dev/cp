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
    vec<pii> s(n);
    rep(i, 0, n) cin >> s[i].first >> s[i].second;
    sort(all(s), [&](pii a, pii b) {
        return a.second < b.second;
    });

    int t = 0, num = 0;
    for (auto p : s) {
        if (p.first >= t) {
            t = p.second;
            num++;
        }
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
