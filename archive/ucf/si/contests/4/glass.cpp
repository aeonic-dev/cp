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

// more aliases
#define pb push_back
#define eb emplace_back

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

struct node1d {
    int l, r;
    ll lazy, max;
    node1d *left, *right;

    node1d(int l, int r) : l(l), r(r), lazy(0), max(0), left(nullptr), right(nullptr) {}

    ~node1d() {
        delete left;
        delete right;
    }

    void increment(int l, int r, int amt);

    void push();

    ll get_max();
};

void node1d::increment(int l, int r, int amt) {
    if (l > this->r || r < this->l) return;
    if (l <= this->l && r >= this->r) {
        lazy += amt;
        max += amt;
        return;
    }

    push();
    left->increment(l, r, amt);
    right->increment(l, r, amt);
    max = ::max(left->max, right->max);
}

void node1d::push() {
    if (left == nullptr) left = new node1d(l, (l + r) / 2);
    if (right == nullptr) right = new node1d((l + r) / 2 + 1, r);

    if (lazy != 0) {
        left->increment(l, r, lazy);
        right->increment(l, r, lazy);
        lazy = 0;
    }
}

ll node1d::get_max() {
    push();
    return max;
}

template<typename node_t, typename data_t>
struct node {
    int lo, hi; // Node range (inclusive, 1-indexed)
    node_t *left, *right; // Children
    data_t data; // Node data container
    bool initialized = false; // Initialization flag because virtual constructors are weird in c++

    node(int lo, int hi) : lo(lo), hi(hi), left(nullptr), right(nullptr) {
        static_assert(std::is_base_of<node<node_t, data_t>, node_t>::value, "");
    }

    virtual ~node() {
        delete left;
        delete right;
    }

    bool is_leaf() {
        return lo == hi;
    }

    int width() {
        return hi - lo;
    }

protected:
    // Pushes updates to children (and creates them if they don't exist). If recursive=true, updates all the way down.
    void push(bool recursive = false) {
        if (!initialized) {
            initialized = true;

            if (is_leaf()) make_leaf(lo);
            else {
                if (left == nullptr) left = make_node(lo, (lo + hi) / 2);
                if (right == nullptr) right = make_node((lo + hi) / 2 + 1, hi);
            }
        }

        update();
        if (recursive && !is_leaf()) {
            left->push(true);
            right->push(true);
        }

        if (!is_leaf()) combine(left->data, right->data);
    }

    // Creates a node. Should probably just call your constructor with new.
    virtual node_t *make_node(int lo, int hi) = 0;

    // Applies any lazy updates to the current node. Should also push updates to direct children, if this is not a leaf node.
    // Push will be called again on children after this method if flushing before a query. The combine function will be called after this method.
    virtual void update() {}

    // Initializes the data container for a leaf node (lo = hi).
    virtual void make_leaf(int i) = 0;

    // Updates the data container for a node from its childrens' data (after lazy updates are pushed).
    virtual void combine(const data_t &l, const data_t &r) = 0;
};

struct seg2d {
    node1d *tree;
};

struct node2d : node<node2d, seg2d> {

};

void solve() {

}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}