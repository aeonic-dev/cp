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
#define mp make_pair

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

struct sneetch_data {
    bool left_bit, right_bit; // Value of leftmost and rightmost bits in range
    int left_bit_count, right_bit_count; // Number of contiguous equal bits on left and right of range

    int max_on_count, max_off_count; // Max contiguous section of on and off bits in the subtree

    bool lazy = false; // Lazy update flag
    int lazy_left = -1, lazy_right = -1; // Lazy update range
};

string sneetch_string; // Initial sneetch configuration

struct node {
    // Node data container type
    typedef sneetch_data data_t;

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

    void indent(int depth) {
        rep(i, 0, depth) cout << "|  ";
    }

    void print(int depth) {
        cout << "[" << lo << ", " << hi << "] {\n";
        indent(depth);
        cout << "|  Left bits:    " << data.left_bit_count << " x " << data.left_bit << endl;
        indent(depth);
        cout << "|  Right bits:   " << data.right_bit_count << " x " << data.right_bit << endl;
        indent(depth);
        cout << "|  Max on bits:  " << data.max_on_count << endl;
        indent(depth);
        cout << "|  Max off bits: " << data.max_off_count << endl;
        indent(depth);
        cout << "|  Lazy: " << data.lazy << " at [" << data.lazy_left << ", " << data.lazy_right << "]\n";
        if (!is_leaf()) {
            indent(depth);
            cout << "|  Left: ";
            left->print(depth + 1);
            indent(depth);
            cout << "|  Right: ";
            right->print(depth + 1);
        }
        indent(depth);
        cout << "}\n";
    }

    // Whether this is a leaf node (only spans one index)
    bool is_leaf() {
        return lo == hi;
    }

    // Number of indices in this node's purview
    int width() {
        return hi - lo + 1;
    }

    // Propagates updates to children and recomputes data for this node
    void push() {
        if (is_leaf() || !data.lazy) return;

        left->flip(data.lazy_left, data.lazy_right);
        right->flip(data.lazy_left, data.lazy_right);

        merge(left->data, right->data);

        data.lazy = false;
        data.lazy_left = data.lazy_right = -1;
    }

    void flip(int l, int r) {
        if (l > hi || r < lo) return;

        if (l <= lo && r >= hi) {
            // Flip all values for this node
            data.left_bit = !data.left_bit;
            data.right_bit = !data.right_bit;
            swap(data.max_on_count, data.max_off_count);

            if (data.lazy) {
                data.lazy = false;
                data.lazy_left = data.lazy_right = -1;
            } else {
                if (!is_leaf()) {
                    // Lazily update children
                    data.lazy = true;
                    data.lazy_left = l;
                    data.lazy_right = r;
                }
            }

            return;
        }

        // Partial cover: update children now and recompute values
        // Partial cover implies this is not a leaf node, so we don't need extra checks
        push();

        left->flip(l, r);
        right->flip(l, r);

        merge(left->data, right->data);
    }

    // Initializes the data container for a leaf node (lo = hi)
    void make_leaf(int i) {
        data.left_bit = data.right_bit = sneetch_string[i - 1] == 'S';
        data.left_bit_count = data.right_bit_count = 1;

        data.max_on_count = data.left_bit;
        data.max_off_count = !data.left_bit;
    }

    // Recomputes the data container for a node from its children's data
    // (after lazy updates are pushed)
    void merge(const data_t &l, const data_t &r) {
        // Update left and rightmost bit values
        data.left_bit = l.left_bit;
        data.right_bit = r.right_bit;

        // Update left and right bit counts

        if (l.left_bit_count < left->width()) data.left_bit_count = l.left_bit_count;
        else {
            // If the left and right children start with the same bit, our left
            // bit section spans to the end of the right child's left bit section
            // Otherwise it's just the width of the left child
            data.left_bit_count = left->width();
            if (l.left_bit == r.left_bit) data.left_bit_count += r.left_bit_count;
        }

        if (r.right_bit_count < right->width()) data.right_bit_count = r.right_bit_count;
        else {
            data.right_bit_count = right->width();
            if (r.right_bit == l.right_bit) data.right_bit_count += l.right_bit_count;
        }

        // Update max length values

        data.max_on_count = max(l.max_on_count, r.max_on_count);
        data.max_off_count = max(l.max_off_count, r.max_off_count);

        if (l.right_bit) {
            int temp = l.right_bit_count;
            if (r.left_bit) temp += r.left_bit_count;
            data.max_on_count = max(data.max_on_count, temp);
        } else {
            int temp = l.right_bit_count;
            if (!r.left_bit) temp += r.left_bit_count;
            data.max_off_count = max(data.max_off_count, temp);
        }

        if (l.left_bit) data.max_on_count = max(data.max_on_count, l.left_bit_count);
        else data.max_off_count = max(data.max_off_count, l.left_bit_count);

        if (r.right_bit) data.max_on_count = max(data.max_on_count, r.right_bit_count);
        else data.max_off_count = max(data.max_off_count, r.right_bit_count);

        if (r.left_bit) data.max_on_count = max(data.max_on_count, r.left_bit_count);
        else data.max_off_count = max(data.max_off_count, r.left_bit_count);
    }

    pi max_contiguous_regions() {
        push();

        return {data.max_on_count, data.max_off_count};
    }
};

void solve() {
    int n, s, l, r;
    cin >> n >> s;

    cin >> sneetch_string;
//    transform(all(sneetch_string), sneetch_string.begin(), ::toupper);

    node *root = new node(1, n);
    rep(i, 0, s) {
        cin >> l >> r;
        root->flip(l, r);

        pi out = root->max_contiguous_regions();
//        root->print(0);
        cout << out.first << " " << out.second << endl;
    }

    delete root;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}