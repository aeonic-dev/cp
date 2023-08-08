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

int last_idx = -1;

namespace trie {
    struct node {
        node *parent;
        node *children[26]{};
        bool is_valid_word;
        int valid_paths;
        int index;
        int depth;

        node(node *parent);

        node(node *parent, int depth);

        ~node() {
            for (int i = 0; i < 26; i++) delete children[i];
        }

    public:
        void add(string s);

        int count_prefix(string s) {
            node *cur = this;

            for (int i = 0; i < s.size(); i++) {
                if (cur->children[s[i] - 'a'] == nullptr) return 0;
                cur = cur->children[s[i] - 'a'];
            }

            return cur->valid_paths;
        }

        int count_pairs() {
            if (valid_paths < 2) return 0;
            if (valid_paths == 2) return 1;

            int num = 0;
            for (int i = 0; i < 26; i++) {
                if (children[i] != nullptr) num += children[i]->count_pairs();
            }

            return num;
        }
    };

    class string_trie {
        node *root;

    public:
        string_trie() : root(new node(nullptr)) {}

        ~string_trie() {
            delete root;
        }

        void add(string s) {
            root->add(s);
        }

        int count_prefix(string s) {
            return root->count_prefix(s);
        }
    };
}

trie::node *nodes[100001];

trie::node::node(trie::node *parent) : parent(parent),
                                       index(++last_idx),
                                       is_valid_word(false),
                                       valid_paths(0),
                                       depth(0) {
    nodes[index] = this;
}

trie::node::node(trie::node *parent, int depth) : parent(parent),
                                                  index(++last_idx),
                                                  is_valid_word(false),
                                                  valid_paths(0),
                                                  depth(depth) {
    nodes[index] = this;
}

void trie::node::add(std::string s) {
    node *cur = this;
    int cur_depth = depth;

    for (int i = 0; i < s.size(); i++) {
        cur->valid_paths++;
        if (cur->children[s[i] - 'a'] == nullptr) cur->children[s[i] - 'a'] = new node(nullptr, cur_depth);
        cur = cur->children[s[i] - 'a'];
        cur_depth++;
    }

    cur->valid_paths++;
    cur->is_valid_word = true;
}

map<int, vec<int>> jumps;

trie::node *jump(trie::node *node, int height) {
    if (height == 0) return node;


}

//    int l2d = log2(height);
//    if (jumps.find(node->index) == jumps.end())
//        jumps[node->index] = vi(l2d + 1, -1);
//
//    if (jumps[node->index][l2d] != -1) return nodes[jumps[node->index][l2d]];
//
//    return jumps[node->index][l2d] = jump(jump(node, height - (1 << l2d)), 1 << l2d);
//}

int solve(int x, int y) {
    trie::node *nx = nodes[x];
    trie::node *ny = nodes[y];

    if (nx->depth < ny->depth) swap(nx, ny);
    int height = nx->depth - ny->depth;

    nx = nodes[]
}

void solve() {
    int q;
    cin >> q;

    trie::string_trie trie;

    char c;
    string w;
    int id, x, y;
    rep(i, 0, q) {
        cin >> c;
        switch (c) {
            case 'T':
                cin >> id >> w;
                trie.add(w, id);
                break;
            case 'E':
                cin >> x >> y;
                cout << solve(x, y) << endl;
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}