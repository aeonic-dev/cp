#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    cin >> n;
    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];
    sort(all(s));

    ll sum = 0;
    rep(i, 0, n) {
        if (s[i] > sum + 1) break;
        sum += s[i];
    }
    cout << sum + 1 << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
