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

const ld pi = acos(-1), eps = 1e-10;

ld angle(ld a, ld b, ld s) {
    return abs(acos(
            (a * a + b * b - s * s) /
            (2 * a * b)
    ));
}

ld find(ld a, ld b, ld c, ld lo, ld hi, int d = 0) {
    ld s = (lo + hi) / 2;
    if (d >= 10000) return -1;

    ld dif = angle(a, b, s) +
             angle(b, c, s) +
             angle(a, c, s) - 2 * pi;
    if (abs(dif) < eps) return s;

    if (dif > 0) return find(a, b, c, lo, s, d + 1);
    return find(a, b, c, s, hi, d + 1);
};

void solve() {
    ld a, b, c;
    cin >> a >> b >> c;

    if (a == 0) {
        if (b == 0 || b != c) cout << "-1\n";
        else cout << b << '\n';

        return;
    }

    if (b == 0) {
        if (a == 0 || a != c) cout << "-1\n";
        else cout << a << '\n';

        return;
    }

    if (c == 0) {
        if (a == 0 || a != b) cout << "-1\n";
        else cout << a << '\n';

        return;
    }

    ld s = find(a, b, c,
                max(abs(a - b), max(abs(b - c), abs(a - c))),
                min(a + b, min(b + c, a + c)));
    if (s == -1) {
        cout << -1 << endl;
        return;
    }

    ld res = s * s * sqrt(3) / 4;
    cout << res << '\n';
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
