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

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<ll, ll> pll;
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
// @formatter:on

vec<ll> cap; // capacity of i-th basket
vec<pair<int, ll>> updates; // update for i-th day: {basket, apples}
map<int, vec<pair<int, pi>>> queries;// queries for day d: {i, {l, r}}
vec<ll> res; // i-th query result

struct node {
    // Node data container type
    typedef ll data_t;

    int lo, hi; // Node range (inclusive, 1-indexed)
    node *left, *right; // Children
    data_t data; // Node data container

    node(int lo, int hi) : lo(lo), hi(hi) {
        if (is_leaf()) make_leaf(lo);
        else {
            left = new node(lo, (lo + hi) / 2);
            right = new node((lo + hi) / 2 + 1, hi);

            merge(left->data, right->data);
        }
    }

    ~node() {
        if (is_leaf()) return;

        delete left;
        delete right;
    }

    // Whether this is a leaf node (only spans one index)
    bool is_leaf() {
        return lo == hi;
    }

    // Adds apples to i-th basket, 1-indexed
    void add(int i, ll apples) {
        if (i > hi || i < lo) return;

        if (is_leaf()) {
            data += apples;
            if (data > cap[i - 1]) data = cap[i - 1];
            return;
        }

        left->add(i, apples);
        right->add(i, apples);
        merge(left->data, right->data);
    }

    // Initializes the data container for a leaf node (lo = hi)
    void make_leaf(int i) {
        data = 0;
    }

    // Recomputes the data container for a node from its children's data
    // (after lazy updates are pushed)
    void merge(const data_t &l, const data_t &r) {
        data = l + r;
    }

    // Counts apples within the given range
    ll count(int l, int r) {
        if (r < lo || l > hi) return 0;

        if (l <= lo && r >= hi) {
            return data;
        }

        return left->count(l, r) + right->count(l, r);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    cap = vec<ll>(n);
    cin >> cap;

    updates = vec<pair<int, ll>>(m);
    cin >> updates;

    rep(i, 0, q) {
        int d, l, r;
        cin >> d >> l >> r;

        if (queries.find(d) == queries.end()) queries[d] = vec<pair<int, pi>>();
        queries[d].push_back({i, {l, r}});
    }

    res = vec<ll>(q, -1);
    node *root = new node(1, n);

    rep(d, 0, m) {
        auto &p = updates[d];
        root->add(p.first, p.second);

        travis(qu, queries[d + 1]) {
            res[qu.first] = root->count(qu.second.first, qu.second.second);
        }
    }

    travis(r, res) cout << r << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs cap-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
}