#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n;
    cin >> n;
    int tar = 0;
    vec<int> s(n);
    rep(i, 0, n) {
        cin >> s[i];
        tar += s[i];
    }
    tar /= n;

    int ex = 0;
    for (auto v : s) {
        if (v < tar) {
            int need = tar - v;
            if (ex < need) return void(cout << "NO\n");
            ex -= need;
        } else ex += v - tar;
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
