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

void solve() {
    int n;
    cin >> n;

    vector<int> v(n);
    vector<int> ind(1000001, -1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];

        if (v[i] == 1 && ind[1] != -1) {
            ind[0] = i + 1;
        } else {
            ind[v[i]] = i + 1;
        }
    }

    vector<int> fib;
    fib.push_back(0);
    fib.push_back(1);

    while (fib[fib.size() - 1] <= 1000000) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }

    for (int i = 0; i < fib.size() - 1; i++) {
        if (i == 1) continue;
        if (ind[fib[i]] >= 0 && ind[fib[i + 1]] >= 0) {
            cout << ind[fib[i]] << " " << ind[fib[i + 1]] << endl;
            return;
        }
    }

    cout << "impossible" << endl;
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
