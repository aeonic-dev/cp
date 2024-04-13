#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
const double pi = acos(-1);

void solve() {
    ld s, r;
    cin >> s >> r;

    if (2 * r <= s) {
        cout << pi * r * r << "\n";
        return;
    }

    if (sqrt(s * s / 2) <= r + 1e-9) {
        cout << s * s << endl;
        return;
    }

    ld y = sqrt(r * r - s * s / 4);
    ld theta = 2 * atan(2 * y / s);
    ld slice = (r * r / 2) * (theta - sin(theta));

    cout << pi * r * r - slice * 4 << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    cout << setprecision(2) << fixed;
    while (t--) solve();

    return 0;
}
