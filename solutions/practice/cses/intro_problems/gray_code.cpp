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
    int n;
    cin >> n;
    rep(i, 0, pow(2, n)) {
        bitset<32> s(i);
        for (int j = n - 1; j >= 0; j--) cout << s[j];
        cout << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
