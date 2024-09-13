#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    cin >> n;

    vec<int> k(n);
    rep(i, 0, n) cin >> k[i];

    set<int> s{k[0]};
    size_t max = 1;
    int l = 0, r = 1;
    while (l < n && r < n) {
        int cur = k[r++];
        if (s.count(cur)) {
            while (true) {
                int rem = k[l++];
                s.erase(rem);
                if (rem == cur) break;
            }
        }

        s.insert(cur);
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
