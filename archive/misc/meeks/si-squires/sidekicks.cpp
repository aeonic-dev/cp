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
// @formatter:on

vec<ll> type_values(6);
vec<int> types;

struct node_data {
    ll sum = 0;
    vec<int> num_per_type = vec<int>(6, 0);
    bool lazy_type = false, lazy_val = false;
    int lazy_type_i, lazy_type_ot, lazy_type_nt;
    int lazy_val_type;
    ll lazy_val_ov, lazy_val_nv;
};

struct node {
    // Node data container type
    typedef node_data data_t;

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

    // Push lazy updates
    void push() {
        if (is_leaf() || !(data.lazy_type || data.lazy_val)) return;

        if (data.lazy_type) {
            left->change_type(data.lazy_type_i, data.lazy_type_ot, data.lazy_type_nt);
            right->change_type(data.lazy_type_i, data.lazy_type_ot, data.lazy_type_nt);
            data.lazy_type = false;
        }

        if (data.lazy_val) {
            left->change_value(data.lazy_val_type, data.lazy_val_ov, data.lazy_val_nv);
            right->change_value(data.lazy_val_type, data.lazy_val_ov, data.lazy_val_nv);
            data.lazy_val = false;
        }

        merge(left->data, right->data);
    }

    // Change the type of a given leaf, 0-indexed
    void change_type(int i, int old_type, int new_type) {
        if (i < lo || i > hi) return;

        if (is_leaf()) {
            if (lo == i) {
                data.num_per_type[old_type] = 0;
                data.sum = type_values[new_type];
                data.num_per_type[new_type] = 1;
            }

            return;
        }

        // Lazy prop
        push();
        data.sum -= type_values[old_type];
        data.sum += type_values[new_type];
        data.num_per_type[old_type]--;
        data.num_per_type[new_type]++;

        data.lazy_type = true;
        data.lazy_type_i = i;
        data.lazy_type_ot = old_type;
        data.lazy_type_nt = new_type;
    }

    // Changes the value of a given type
    void change_value(int type, ll old_value, ll new_value) {
        if (data.num_per_type[type] < 1) return;

        if (is_leaf()) {
            if (types[lo] == type) data.sum = new_value;
            return;
        }

        // Lazy prop
        push();
        data.sum -= data.num_per_type[type] * old_value;
        data.sum += data.num_per_type[type] * new_value;

        data.lazy_val = true;
        data.lazy_val_type = type;
        data.lazy_val_ov = old_value;
        data.lazy_val_nv = new_value;
    }

    // Initializes the data container for a leaf node (lo = hi)
    void make_leaf(int i) {
        data.sum = type_values[types[i]];
        data.num_per_type[types[i]] = 1;
    }

    // Recomputes the data container for a node from its children's data
    // (after lazy updates are pushed)
    void merge(const data_t &l, const data_t &r) {
        data.sum = 0;
        rep(i, 0, 6) {
            data.num_per_type[i] = l.num_per_type[i] + r.num_per_type[i];
            data.sum += data.num_per_type[i] * type_values[i];
        }
    }

    // Sum values within the given range, 0-indexed
    ll sum(int l, int r) {
        if (r < lo || l > hi) return 0;

        push();
        if (l <= lo && r >= hi) {
            return data.sum;
        }

        return left->sum(l, r) + right->sum(l, r);
    }
};

void solve() {
    int n, q;
    cin >> n >> q >> type_values;
    types = vec<int>(n);
    rep(i, 0, n) {
        char ch;
        cin >> ch;
        types[i] = (ch - '1');
    }
    cin.ignore();

    node *root = new node(0, n - 1);
    rep(i, 0, q) {
        int tmp, a, b;
        cin >> tmp >> a >> b;
        switch (tmp) {
            case 1:
                root->change_type(a - 1, types[a - 1], b - 1);
                types[a - 1] = b - 1;
                break;
            case 2:
                root->change_value(a - 1, type_values[a - 1], b);
                type_values[a - 1] = b;
                break;
            case 3:
                cout << root->sum(a - 1, b - 1) << endl;
            default:
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}