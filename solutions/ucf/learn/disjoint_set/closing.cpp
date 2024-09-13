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

struct dsu {
    vector<int> par;

    dsu(int n) : par(n, -1) {}

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b];
        par[b] = a;

        return true;
    }

    int find(int s) {
        return par[s] < 0 ? s : par[s] = find(par[s]);
    }

    int count() {
        int num = 0;
        for (auto &p: par) num += p < 0;
        return num;
    }
};

void solve() {
    int n, m, a, b;
    cin >> n >> m;

    vec<vi> edges(n);
    bitset<200000> open;

    rep(i, 0, m) {
        cin >> a >> b;
        edges[a - 1].pb(b - 1);
        edges[b - 1].pb(a - 1);
    }

    vec<int> closing(n);
    rep(i, 0, n) {
        cin >> closing[i];
        open[--closing[i]] = false;
    }
    reverse(all(closing));

    dsu s(n);
    rep(i, 0, n) {
        travis(e, edges[i]) {
            if (open[i] && open[e]) s.join(i, e);
        }
    }

    vec<bool> res(n);
    int components = s.count();

    rep(i, 0, n) {
        int barn = closing[i];
        open[barn] = true;

        travis(e, edges[barn]) {
            if (open[e]) components -= s.join(barn, e);
        }

        res[n - i - 1] = components == n - i;
    }

    rep(i, 0, n) {
        cout << (res[i] ? "YES" : "NO") << endl;
    }
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