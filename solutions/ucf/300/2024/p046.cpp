#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld pi = acos(-1);

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double) dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { 
        ld res = atan2l(y, x);
        if (res < 0) res = 2 * pi - res;
        return res;
    }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef Point<ld> P;

// #include "geo.h"
void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vi subsz(n, -1);
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b, a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto get_subsz = [&](int u, int l, auto &get_subz) -> int {
        int &res = subsz[u] = 1;
        for (int v : adj[u]) {
            if (v == l) continue;
            res += get_subz(v, u, get_subz);
        }
        return res;
    };
    auto get_centroid = [&](int u, int l, auto &get_centroid) -> int {
        for (int v : adj[u]) {
            if (v == l) continue;
            if (subsz[v] > n / 2) return get_centroid(v, u, get_centroid);
        }
        return u;
    };

    get_subsz(0, -1, get_subsz);
    int root = get_centroid(0, -1, get_centroid);

    // vi num_leaves(n);
    // auto get_numl = [&](int u, int l, auto &get_numl) -> int {
    //     // gets the number of leaf nodes in the subtree rooted at u
    //     int &res = num_leaves[u] = 0;
    //     for (int v : adj[u]) {
    //         if (v == l) continue;
    //         res += get_numl(v, u, get_numl);
    //     }
    //     if (res == 0) res = 1;
    //     return res;
    // };
    // get_numl(root, -1, get_numl);

    vector<P> pos(n);
    pos[root] = {0, 0};

    // GD_INIT("vis.html");
    int num = 0;
    auto get_pos = [&](int u, int l, auto &get_pos) -> void {
        // recursively place points with distance of 1, dtheta apart radially
        // return the deepest and furthermost (radially) point that we placed

        // cout << "get_pos(" << u << ", " << l << ", " << min_theta << ")" << endl;
        // cout << "theta = " << theta << ", u is at " << pos[u] << "\n\n";
        for (int v : adj[u]) {
            if (v == l) continue;

            ld theta = 2 * pi * num / (n - 1);
            pos[v] = pos[u] + P(cosl(theta), sinl(theta)), num++;
            // GD_SEGMENT(pos[u].x * 1000, pos[u].y * 1000, pos[v].x * 1000, pos[v].y * 1000, "black");
            // GD_POINT(pos[v].x * 1000, pos[v].y * 1000, "black") << setprecision(10) << fixed << "v = " << pos[v] * 1000 << ", theta = " << theta;

            get_pos(v, u, get_pos);
        }
    };
    get_pos(root, -1, get_pos);

    cout << setprecision(10) << fixed;
    rep(i, 0, n) {
        P a = pos[i];
        rep(j, 0, n) {
            if (i == j) continue;
            P b = pos[j];
            assert((b - a).dist() > 1e-6);
        }
        cout << a.x << " " << a.y << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
