// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// aliases
#define vec vector
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// meta macros
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define THANKS void GIVE_ME_A_SEMICOLON() // requires semicolon when calling a macro

// more aliases
#define pb push_back
#define eb emplace_back
#define mp make_pair

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define numeric(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

template<typename n_t>
struct pt {
    n_t x, y;

    pt() : x(0), y(0) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    pt(n_t x, n_t y) : x(x), y(y) {}

    pt operator+(pt u) const {
        return {x + u.x, y + u.y};
    }

    pt operator-(pt u) const {
        return {x - u.x, y - u.y};
    }

    pt operator*(n_t d) const {
        return {x * d, y * d};
    }

    pt operator/(n_t d) const {
        return {x / d, y / d};
    }

    bool operator==(const pt &u) const {
        return x == u.x && y == u.y;
    }

    n_t distance(pt u) const {
        return sqrt(std::pow(x - u.x, 2) + std::pow(y - u.y, 2));
    }

    n_t dot(pt u) const {
        return x * u.x + y * u.y;
    }

    n_t cross(pt u) const {
        return x * u.y - y * u.x;
    }

    n_t cross(pt u, pt v) const {
        return (u - *this).cross(v - *this);
    }

    n_t norm() const {
        return x * x + y * y;
    }

    n_t mag() const {
        return std::sqrt(norm());
    }

    pt unit() const {
        n_t m = mag();
        return {x / m, y / m};
    }

    // Projects the vector u onto this vector
    pt project(pt u) const {
        return unit() * dot(u) / mag();
    }
};


template<typename n_t = int, typename f_t = int, f_t infinity = INT_MAX>
struct ffa {
    n_t n;
    vector<vector<f_t>> residual;
    vector<bool> seen;

    ffa(n_t n) : n(n) {
        static_assert(is_integral<n_t>::value, "node index type must be integral");
        static_assert(is_integral<f_t>::value, "flow value type must be integral");

        residual = vector<vector<f_t>>(n, vector<f_t>(n));
    }

    // Adds an edge to the network
    void add_edge(n_t u, n_t v, f_t capacity, bool bidirectional = false) {
        residual[u][v] += capacity;
        if (bidirectional) residual[v][u] += capacity;
    }

    // Find augmenting paths in the network
    f_t dfs(n_t cur, n_t t, f_t flow) {
        if (cur == t) return flow;

        for (n_t next = 0; next < n; next++) {
            if (residual[cur][next] == 0 || seen[next]) continue;

            seen[next] = true;
            f_t f = dfs(next, t, min(flow, residual[cur][next]));
            if (f != 0) {
                residual[cur][next] -= f;
                residual[next][cur] += f;
                return f;
            }
        }

        return 0;
    }

    // Gets the max flow from s to t
    f_t max_flow(n_t s, n_t t) {
        f_t flow = 0;

        while (true) {
            seen = vector<bool>(n, false);
            seen[s] = true;

            f_t f = dfs(s, t, infinity);
            if (f == 0) break;

            flow += f;
        }

        return flow;
    }
};

typedef pt<li> lpt;

int sign(li n) {
    if (n == 0) return 0;
    return n < 0 ? -1 : 1;
}

struct obs {
    lpt a, b;

    bool is_vertical() {
        return a.x == b.x;
    }

    bool intersects(obs o) {
        if (is_vertical()) {
            li x = a.x, oy = o.a.y;

            if ((x >= o.a.x && x <= o.b.x) || (x >= o.b.x && x <= o.a.x)) {
                return (oy <= a.y && oy >= b.y) || (oy <= b.y && oy >= a.y);
            }
        } else {
            li y = a.y, ox = o.a.x;

            if ((y >= o.a.y && y <= o.b.y) || (y >= o.b.y && y <= o.a.y)) {
                return (ox <= a.x && ox >= b.x) || (ox <= b.x && ox >= a.x);
            }
        }

        return false;
    }
};

void solve() {
    int n;
    cin >> n;

    vec<obs> horizontal;
    vec<obs> vertical;

    rep(i, 0, n) {
        obs o;
        cin >> o.a.x >> o.a.y >> o.b.x >> o.b.y;
        (o.is_vertical() ? vertical : horizontal).push_back(o);
    }

    // 0 = source, 1 = sink, 2->2+i = horizontal, 2->2+horizontal.size()+i = vertical
    ffa<> network(2 + n);

    rep(h, 0, horizontal.size()) {
        int i_h = 2 + h;
        network.add_edge(0, i_h, INT_MAX);

        rep(v, 0, vertical.size()) {
            int i_v = 2 + horizontal.size() + v;
            if (h == 0) network.add_edge(i_v, 1, INT_MAX);

            if (horizontal[h].intersects(vertical[v])) {
                cout << "intersection at " << h << ", " << v << endl;
                network.add_edge(i_h, i_v, 1);
//                network.add_edge(i_v, i_h, 1);
            }
        }
    }

    ll vertices = network.n;
    ll max_flow = network.max_flow(0, 1);
    cout << "vertices " << vertices << endl;
    cout << "max flow " << max_flow << endl;
    cout << (n - max_flow) << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
