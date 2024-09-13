#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n;
    cin >> n;
    set<int> s{0};

    int res = 0;
    rep(i, 0, n) {
        int x;
        cin >> x;

        // cout << "\nbefore playing " << x << "\n";
        // for (int i : s) cout << i << " ";
        // cout << "-> " << res << "\n";

        int cur = *s.rbegin();
        if (cur == x) continue;
        if (cur < x) {
            s.insert(x), res++;
            continue;
        }

        while ((cur = *s.rbegin()) > x) s.erase(cur), res++;
        if (cur != x) s.insert(x), res++;
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
