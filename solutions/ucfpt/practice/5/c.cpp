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

void solve() {
    int n, l, h;
    cin >> n >> l >> h;

    vec<ll> pfx(n + 1, 0);
    vec<vec<int>> profitable(h - l + 1); // # profitable segments for {len, offset}
    rep(len, l, h + 1) profitable[len - l] = vec<int>(len, 0);

    int p;
    rep(i, 0, n) {
        cin >> p;
        pfx[i + 1] = pfx[i] + p;

        // skip first index (all zeroes here)
        if (i == 0) continue;

        rep(len, l, h + 1) {
            int o = i % len; // offset
            int s = max(0, i - len); // start of the segment that just ended

            // sum of the segment that just ended
            ll sum = pfx[i] - pfx[s];
            profitable[len - l][o] += sum > 0;

//            cout << "i=" << i << "\tlen=" << len << "\to=" << o << endl;
//            cout << "[" << s << ", " << i << ") -> " << sum << "\n\n";
        }
    }

    int min = INT_MAX, max = 0;
    rep(len, l, h + 1) {
        rep(o, 0, len) {
            int s = n - (n % len) - (len - o);
            if (n - s > len) s += len;
            s = ::max(s, 0);
//            ll s = ::max(0LL, n - (len - o));
////            if (n - s > len) s += len;
            ll sum = pfx[n] - pfx[s];

//            cout << "len=" << len << "\to=" << o << endl;
//            cout << "[" << s << ", " << n - 1 << "] -> " << sum << "\n\n";

            auto &res = profitable[len - l][o];
            res += sum > 0;

            min = ::min(min, res);
            max = ::max(max, res);
        }
    }

    cout << min << " " << max << endl;
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