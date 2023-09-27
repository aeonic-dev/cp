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

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
// @formatter:on

void unset_bit(ll &mask, int i) {
    mask &= ~(1 << i);
}

void set_bit(ll &mask, int i, bool val = true) {
    if (val) mask |= (1 << i);
    else unset_bit(mask, i);
}

bool get_bit(ll &mask, int i) {
    return (mask >> i) & 1;
}

//vec<vec<vec<int>>> dp(15, vec<vec<int>>(1 << 15, vec<int>(15, -1))); // k, mask
void go(vec<ld> &num, int n, ll mask, int k, ld fac = 1) {
    if (k == 0) return;

    int carry = 0;
    rev(i, n - 1, -1) {
        if (get_bit(mask, i)) break;
        else carry++;
    }

    rep(i, 0, n) {
        if (get_bit(mask, i)) {
            ld ways = 1 + carry;
            ld p = ways * fac / (ld) n;
            carry = 0;

            if (k == 1) num[i] += p;
            set_bit(mask, i, false);
            go(num, n, mask, k - 1, p);
            set_bit(mask, i, true);
        } else carry++;
    }
}

void solve() {
    int n, k, tmp;
    cin >> n >> k;

    vec<ld> num(n, 0);
    ll mask = 0;
    rep(i, 0, n) {
        cin >> tmp;
        if (tmp == 1) set_bit(mask, i);
    }

    go(num, n, mask, k);
    cout << setprecision(8) << fixed;
    rep(i, 0, n) {
        ld val = num[i];// / pow((ld) n, k);
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
//    solve();
}