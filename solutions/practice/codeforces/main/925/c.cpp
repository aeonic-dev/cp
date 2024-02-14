#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n;
    cin >> n;

    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];

    int pfxn = s[0], sfxn = s.back();
    int pfx = 1, sfx = 1;
    rep(i, 1, n) {
        if (s[i] != s[i - 1]) break;
        pfx++;
    }
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] != s[i + 1]) break;
        sfx++;
    }

    if (pfx == n) return void(cout << "0\n");
    if (pfxn == sfxn) return void(cout << (n - pfx - sfx) << "\n");

    int res = min(n - pfx, n - sfx);
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
