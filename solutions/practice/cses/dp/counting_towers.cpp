#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int MAXN = 1000000;
const ll mod = 1e9 + 7;
vll tg(MAXN + 1, 1), ap(MAXN + 1, 1);

void solve() {
    int n;
    cin >> n;
    cout << (tg[n] + ap[n]) % mod << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    rep(i, 2, MAXN + 1) {
        tg[i] = ((tg[i - 1] * 2) % mod + ap[i - 1]) % mod;
        ap[i] = ((ap[i - 1] * 4) % mod + tg[i - 1]) % mod;
    }

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
