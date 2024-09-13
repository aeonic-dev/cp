#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    string s;
    cin >> s;

    rep(i, 1, s.size()) {
        string a = s.substr(0, i);
        string b = s.substr(i, s.size() - i);
        if (a[0] != '0' && b[0] != '0' && stol(a) < stol(b)) {
            cout << a << " " << b << endl;
            return;
        }
    }

    cout << -1 << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
