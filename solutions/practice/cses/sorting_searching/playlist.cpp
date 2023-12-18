#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, x;
    cin >> n;

    unordered_set<int> s;
    size_t max = 0;
    rep(i, 0, n) {
        cin >> x;
        if (s.count(x)) s.clear();
        s.insert(x);
        max = ::max(max, s.size());
    }

    cout << max << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
