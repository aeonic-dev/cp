#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef vec<int> vi;
typedef long long ll;

array<vi, 2> manacher(const string &s) {
    int n = s.size();
    array<vi, 2> p = {vi(n + 1), vi(n)};
    rep(z, 0, 2) for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r) p[z][i] = min(t, p[z][l + t]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    return p;
}

void solve() {
    string s;
    cin >> s;

    auto r = manacher(s);
    int lo = 0, hi = 0;
    rep(i, 0, s.size()) {
        if (r[0][i] * 2 > hi - lo) {
            lo = i - r[0][i];
            hi = i + r[0][i];
        }

        if (r[1][i] * 2 + 1 > hi - lo) {
            lo = i - r[1][i];
            hi = i + r[1][i] + 1;
        }
    }

    cout << string{s.begin() + lo, s.begin() + hi};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
