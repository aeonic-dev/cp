// Settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// Few word type fast zoom
#define vec vector
#define pb push_back
#define eb emplace_back
#define uset unordered_set
#define umap unordered_map

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<li, li> pli;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// Other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type
#define gin(type) get_cin<type>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

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

    // Finds augmenting paths in the network
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

const ll INF = 1e18;

struct trip {
    int u, v;
    ll start, end;
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    // distance table
    vec<vll> dist(n, vll(n, INF));
    rep(i, 0, n) dist[i][i] = 0;

    // read in roads
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;

        dist[--u][--v] = w;
    }

    // shortest paths
    rep(p, 0, n) {
        rep(i, 0, n) {
            rep(j, 0, n) {
                ll cur = dist[i][p] + dist[p][j];
                if (cur < dist[i][j]) {
                    dist[i][j] = cur;
                }
            }
        }
    }

    // read in trips
    vec<trip> trips(k);
    rep(i, 0, k) {
        trip &t = trips[i];
        cin >> t.u >> t.v >> t.start;
        t.end = t.start + dist[--t.u][--t.v];
    }

    // flow
    int i_source = k * 2, i_sink = i_source + 1;
    ffa<int, ll, LLONG_MAX> f(i_sink + 1);

    rep(i, 0, k) {
        f.add_edge(i_source, i, 1);
        f.add_edge(k + i, i_sink, 1);
        trip &t1 = trips[i];

        rep(j, 0, k) {
            if (i == j) continue;
            trip &t2 = trips[j];

            // add edge if route at i can be paired with route at j
            if (t1.end + dist[t1.v][t2.u] <= t2.start) {
                f.add_edge(i, k + j, 1);
            }
        }
    }

    ll res = f.max_flow(i_source, i_sink);
    cout << k - res << endl;
}

#define MULTIPLE_CASES 0

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}