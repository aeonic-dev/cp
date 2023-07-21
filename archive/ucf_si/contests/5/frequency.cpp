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

void factorize(vec<pair<ll, ll>> &factors, ll a, ll b) {
    ll i = 2;

    while (i * i <= a) {
        int e = 0;
        while (a % i == 0) {
            a /= i;
            e++;
        }

        if (e > 0) factors.eb(i, e * b);
        i++;
    }

    if (a > 1) factors.eb(a, b);
}

template<typename n_t = int, typename f_t = int, f_t infinity = INT_MAX>
struct ffa {
    n_t n;
    vector<vector<f_t>> residual;
    vector<bool> seen;

    ffa(n_t n) : n(n) {
        static_assert(is_integral<n_t>::value, "Node index type must be integral");
        static_assert(is_integral<f_t>::value, "Flow value type must be integral");

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

void solve() {
    int n;
    cin >> n;

    vec<ll> f(n);
    ffa<int, ll, LONG_LONG_MAX> network(2 + n * 2); // 0 = source, 1 = sink, 2->n-1 = left, n->2n = right

    rep(i, 0, n) cin >> f[i];

    rep(i, 0, n) {
        network.add_edge(0, 2 + i, 1);
        network.add_edge(2 + n + i, 1, 1);

        rep(j, 0, n) { // TODO: 0->n or i->n?
            if (i == j) continue;

            ll p = f[i] * f[j];
            if (p % 2 == 0 && p % 4 != 0) {
                vec<pair<ll, ll>> factors;
                factorize(factors, p, 1);

                travis(fact, factors) {
                    if (fact.second > 1) {
//                        cout << f[i] << ", " << f[j] << endl;
                        network.add_edge(2 + i, 2 + n + j, 1);
                        network.add_edge(2 + j, 2 + n + i, 1);
                        break;
                    }
                }
            }
        }
    }

    ll vertices = 2 + n * 2;
    ll max_flow = network.max_flow(0, 1);
    cout << (vertices - max_flow - 2) / 2 << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
