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

void solve() {
    int n, x;
    cin >> n >> x;
    vec<ll> s(n);
    vec<int> ind(n);
    rep(i, 0, n) {
        cin >> s[i];
        ind[i] = i;
    }
    sort(all(ind), [&](int i, int j) {
        return s[i] < s[j];
    });

    int l = 0, r = n - 1;
    while (l != r) {
        ll sum = s[ind[l]] + s[ind[r]];
        if (sum == x) {
            cout << ind[l] + 1 << " " << ind[r] + 1 << endl;
            return;
        }

        if (sum < x) l++;
        else r--;
    }

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
