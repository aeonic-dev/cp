#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < s.size(); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) { // sum of values in [0, pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
    int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= s.size() && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};

struct FT2 {
    vector<vi> ys;
    vector<FT> ft;
    FT2(int limx) : ys(limx) {}
    void fakeUpdate(int x, int y) {
        for (; x < ys.size(); x |= x + 1) ys[x].push_back(y);
    }
    void init() {
        for (vi &v : ys) sort(all(v)), ft.emplace_back(v.size());
    }
    int ind(int x, int y) {
        return (int) (lower_bound(all(ys[x]), y) - ys[x].begin());
    }
    void update(int x, int y, ll dif) {
        for (; x < ys.size(); x |= x + 1)
            ft[x].update(ind(x, y), dif);
    }
    ll query(int x, int y) {
        ll sum = 0;
        for (; x; x &= x - 1)
            sum += ft[x - 1].query(ind(x - 1, y));
        return sum;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vec<bitset<1000>> s(n);
    vec<vec<ll>> pfx(n + 1, vec<ll>(n + 1, 0));
    rep(i, 0, n) {
        string str;
        cin >> str;
        rep(j, 0, n) {
            pfx[i + 1][j + 1] =
                    pfx[i][j + 1] + pfx[i + 1][j] - pfx[i][j]
                    + (s[i][j] = (str[j] == '*'));
        }
    }

    FT2 ft(n + 1);
    vec<array<int, 5>> qs(m);
    rep(i, 0, m) {
        auto &q = qs[i];
        cin >> q[0] >> q[1] >> q[2];
        if (q[0] == 1) ft.fakeUpdate(q[1], q[2]);
        else cin >> q[3] >> q[4];
    }

    ft.init();
    rep(i, 0, m) {
        auto &q = qs[i];
        if (q[0] == 1) {
            auto vb = s[q[1] - 1][q[2] - 1];
            ft.update(q[1], q[2], vb ? -1 : 1);
            vb.flip();
        } else {
            ll sum = pfx[q[3]][q[4]]
                     - pfx[q[3]][q[2] - 1]
                     - pfx[q[1] - 1][q[4]]
                     + pfx[q[1] - 1][q[2] - 1];

            ll fts = ft.query(q[3] + 1, q[4] + 1)
                     - ft.query(q[3] + 1, q[2])
                     - ft.query(q[1], q[4] + 1)
                     + ft.query(q[1], q[2]);

//            cout << sum << " " << fts << "\n";
            cout << sum + fts << "\n";
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
