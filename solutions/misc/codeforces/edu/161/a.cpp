#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

bool isl(char ch) {
    return ch >= 'a' && ch <= 'z';
}

bool isu(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

void solve() {
    int n;
    string p, q, r;
    cin >> n >> p >> q >> r;

    bool cnm = false; // any c that doesn't match
    rep(i, 0, n) {
        char a = p[i], b = q[i], c = r[i];
        if (c != a && c != b) cnm = true;
//        if (isl(a) && isl(b) && a == b) {
//
//        }
    }

    if (cnm) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
