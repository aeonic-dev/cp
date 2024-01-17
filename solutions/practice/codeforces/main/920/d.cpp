#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, m, tmp;
    cin >> n >> m;

    deque<int> a;
    deque<int> b;
    rep(i, 0, n) {
        cin >> tmp;
        a.push_back(tmp);
    }
    rep(i, 0, m) {
        cin >> tmp;
        b.push_back(tmp);
    }
    sort(all(a)), sort(all(b));

    ll res = 0;
    rep(i, 0, n) {
        ll af = a.front(), ak = a.back();
        ll bf = b.front(), bk = b.back();
        ll afbf = abs(af - bf), afbk = abs(af - bk);
        ll akbf = abs(ak - bf), akbk = abs(ak - bk);

        ll max = (::max(afbf, ::max(afbk, ::max(akbf, akbk))));
        res += max;
        if (max == afbf) {
            a.pop_front(), b.pop_front();
        } else if (max == afbk) {
            a.pop_front(), b.pop_back();
        } else if (max == akbf) {
            a.pop_back(), b.pop_front();
        } else if (max == akbk) {
            a.pop_back(), b.pop_back();
        }
    }

    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
