#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef vec<int> vi;
typedef long long ll;

vi Z(const string &S) {
    vi z(S.size());
    int l = -1, r = -1;
    rep(i, 1, S.size()) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < S.size() && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

vi pi(const string &s) {
    vi p(s.size());
    rep(i, 1, s.size()) {
        int g = p[i - 1];
        while (g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

void solve() {
    string s;
    cin >> s;

    auto p = pi(s);
    auto z = Z(s);

    for (auto x: z) cout << x << " ";
    cout << "\n";
    for (auto x: p) cout << x << " ";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
