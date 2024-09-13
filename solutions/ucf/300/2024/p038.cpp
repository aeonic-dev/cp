#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

struct pt {
    ll x, y;
    pt(ll x = 0, ll y = 0) : x(x), y(y) {}
    pt operator+(pt &&p) const { return {x + p.x, y + p.y}; }
    bool operator<(const pt &p) const { return tie(x, y) < tie(p.x, p.y); }
    ll dist(pt &p) { return abs(x - p.x) + abs(y - p.y); }
};

void solve() {
    int n;
    cin >> n;
    vector<pair<pt, ll>> pts(n);
    set<pt> cov;
    rep(i, 0, n) {
        auto &[p, c] = pts[i];
        cin >> p.x >> p.y >> c, c++;
        // silly goofy brain empty way to do the thing
        for (pt o{p.x - c - 1}; o.x <= p.x + c + 1; o.x++) {
            for (o.y = p.y - c - 1; o.y <= p.y + c + 1; o.y++) {
                ll d = p.dist(o);
                if ((o.x == p.x || o.y == p.y) && d == c + 1) continue;
                if (d <= c + 1) cov.insert(o);
            }
        }
    }
    for (auto [p, c] : pts) {
        for (pt o{p.x - c - 2}; o.x <= p.x + c + 2; o.x++) {
            for (o.y = p.y - c - 2; o.y <= p.y + c + 2; o.y++) {
                if (cov.count(o)) continue;
                for (pt s{o.x - 1}; s.x <= o.x; s.x++) {
                    for (s.y = o.y - 1; s.y <= o.y; s.y++) {
                        // check if the 2x2 square is *not* covered
                        if (cov.count(s)
                            || cov.count(s + pt{1, 0})
                            || cov.count(s + pt{0, 1})
                            || cov.count(s + pt{1, 1})) continue;
                        // there is a 2x2 square in complement that includes this cell
                        goto keep;
                    }
                }
                cov.insert(o);
            keep:;
            }
        }
    }
    int res = sz(cov);
    cout << res << "\n";
//     vector<string> gr(20, "....................");
//     for (auto [x, y] : cov) gr[10 - y][x + 10] = 'X';
//     for (string &str : gr) cout << str << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
