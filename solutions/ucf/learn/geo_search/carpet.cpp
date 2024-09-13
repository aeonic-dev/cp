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

const ld pi = acosl(-1);
const ld eps = 1e-6;

ld angle(ld a, ld b, ld s) {
    return acosl(
            (a * a + b * b - s * s)
            / (2 * a * b));
}

void solve() {
    ld a, b, c;
    cin >> a >> b >> c;
    
    ld lo = max({a, b, c});
    ld hi = min({a + b, b + c, c + a});
    if (hi <= lo) return void(cout << -1 << "\n");
    
    auto get_angle = [&](ld s) {
        return angle(a, b, s)
               + angle(b, c, s)
               + angle(c, a, s);
    };
    
    rep(_, 0, 100) {
        ld md = (lo + hi) / 2.0;
        if (get_angle(md) > 2 * pi) hi = md;
        else lo = md;
    }
    ld res = hi;
    if (get_angle(res) < 2 * pi - eps)
        return void(cout << -1 << "\n");
    cout << res * res * sqrtl(3) / 4 << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(3) << fixed;
    
    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();
    
    return 0;
}
