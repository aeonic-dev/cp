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

    bool zero = false;
    vec<int> s(n), neg;
    neg.reserve(n);
    rep(i, 0, n) {
        cin >> s[i];
        if (!s[i]) zero = true;
        else if (s[i] < 0) neg.push_back(i);
    }

    if (zero || neg.size() == 1) {
        cout << "0\n";
        return;
    }

    if (neg.size() > 1) {
        sort(all(neg), [&](int i, int j) { return s[i] > s[j]; });
        if (neg.size() % 2 == 0) {
            cout << "1\n1 0\n";
            return;
        }

        cout << "0\n";
        return;
    }

    cout << "1\n1 0\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
