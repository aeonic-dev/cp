#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    ll n;
    cin >> n;

    if (n < 10) {
        cout << n << endl;
        return;
    }

    ll d = 1, p = 1, skip = 0;
    while (1) {
        n -= skip, skip = 9 * p * d++, p *= 10;
        if (skip >= n) break;
    }
    n--, d--, p /= 10;

    ll num = p + (n / d); // the number we're taking a digit from
    ll ind = n % d; // the index of our digit in num

    char digit = to_string(num)[ind];
    cout << digit << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
