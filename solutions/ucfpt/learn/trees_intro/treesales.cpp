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
#define numeric(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

struct node {
    node *parent;
    vec<node *> children;
    ll subtree_sales;

    node(node *parent, string name);

    ~node() {
        for (node *child : children) delete child;
    }

    void sale(int num) {
        // TODO: if sums are off, include the current node in subtree sales (cur = this)
        node *cur = this;

        while (cur != nullptr) {
            cur->subtree_sales += num;
            cur = cur->parent;
        }
    }
};

map<string, node*> nodes;

node::node(node *parent, string name) : parent(parent), subtree_sales(0) {
    nodes[name] = this;
}

node *root;

void solve(int k) {
    int n;
    cin >> n;

    cout << "COMPANY " << k << endl;

    string s;
    int num;
    rep(i, 0, n) {
        cin >> s;
//        cout << s;
        if (s == "ADD") {
            cin >> s;
            if (s == "ROOT") {
                cin >> s;
                root = new node(nullptr, s);
            } else {
                node *parent = nodes[s];

                cin >> s;
                node *child = new node(parent, s);
                parent->children.pb(child);
            }
        } else if (s == "SALE") {
            cin >> s >> num;
            nodes[s]->sale(num);
        } else if (s == "QUERY") {
            cin >> s;
            cout << nodes[s]->subtree_sales << endl;
        }
    }

    delete root;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests, k = 1;
    cin >> tests;
    while (tests--) solve(k++);
}