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
    vec<int> a, b;
    a.reserve(n), b.reserve(n);
    ll as = 0, bs = 0;
    for (int i = n; i > 0; i--) {
        if (as < bs) a.push_back(i), as += i;
        else b.push_back(i), bs += i;
    }

    if (as != bs) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    cout << a.size() << endl;
    for (auto x : a) cout << x << " ";
    cout << endl << b.size() << endl;
    for (auto x : b) cout << x << " ";
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
