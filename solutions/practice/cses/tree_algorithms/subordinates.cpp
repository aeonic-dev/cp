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

vec<vec<int>> ch;
vec<ll> sub;

ll get(int i) {
    if (ch[i].size() == 0) return 0;
    auto &res = sub[i];
    if (res != -1) return res;

    res = 0;
    for (auto ind: ch[i]) {
        res += 1 + get(ind);
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    ch = vec<vec<int>>(n);
    rep(i, 1, n) {
        int par;
        cin >> par;

        ch[par - 1].push_back(i);
    }

    sub = vec<ll>(n, -1);
    rep(i, 0, n) {
        cout << get(i) << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
