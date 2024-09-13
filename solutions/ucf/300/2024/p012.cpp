#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

int num_nodes;
map<string, int> str_indices;

struct node {
    node *ch[26]{};
    int max_value = -1;
    int max_node = -1, node_index; // max_ind is the node index of max value in the subtree
    bool is_word = false, is_ac_path;

    node(bool ac_path = true) : node_index(num_nodes++), is_ac_path(ac_path) {}
    ~node() { rep(i, 0, 26) delete ch[i]; }

    int add(const string &s, int value, bool ac_path = true) {
        node *cur = this;
        rep(i, 0, sz(s)) {
            char c = s[i];
            if (cur->ch[c - 'a'] == nullptr) cur->ch[c - 'a'] = new node(ac_path);
            cur = cur->ch[c - 'a'];
        }
        cur->is_word = true;
        int res = str_indices[s] = cur->node_index;

        cur = this;
        for (char c : s) {
            cur = cur->ch[c - 'a'];
            if (value > cur->max_value) {
                cur->max_value = value;
                cur->max_node = res;
            }
        }
        if (value > this->max_value) {
            this->max_value = value;
            this->max_node = res;
        }

        return res;
    }

    void add_edges(vector<vector<pair<int, int>>> &adj) {
        if (node_index != 0 
            && node_index != max_node
            && is_ac_path) {
            adj[node_index].emplace_back(max_node, 1);
        }

        rep(i, 0, 26) {
            if (ch[i] != nullptr) {
                adj[node_index].emplace_back(ch[i]->node_index, 1);
                adj[ch[i]->node_index].emplace_back(node_index, 1);
                ch[i]->add_edges(adj);
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    num_nodes = 0;
    node trie;
    rep(i, 0, n) {
        string str;
        cin >> str;
        trie.add(str, n - i);
    }
    vector<string> queries(m);
    rep(i, 0, m) {
        cin >> queries[i];
        trie.add(queries[i], 0, false);
    }

    vector<vector<pair<int, int>>> adj(num_nodes);
    trie.add_edges(adj);

    vector<int> dist(num_nodes, 1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w >= dist[v]) continue;
            pq.emplace(dist[v] = d + w, v);
        }
    }

    rep(i, 0, m) {
        string str = queries[i];
        int res = dist[str_indices[str]];
        cout << res << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
