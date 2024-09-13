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

const ll mod = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    if (a > b * 2 || b > a * 2) {
        cout << "NO\n";
        return;
    }

    a %= 3, b %= 3;
    if ((a == 0) ^ (b == 0)) cout << "NO\n";
    else if (abs(a - b) == 1 || (!a && !b)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
