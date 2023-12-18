#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector

int ind = 0;

struct node {
    node *children[26]{};
    int index;
    int mw = -1, mwi = -1; // max weight of a word in children; index of the child containing it
    int word_count = 0;

    node() : index(ind++) {}

    ~node() { for (auto ch: children) delete ch; }

    // returns the index the word was placed at
    int add(string &s, int w, int idx = 0) {
        if (idx == s.size()) {
            if (w > mw) mw = w, mwi = index;

            word_count++;
            return index;
        }

        int i = s[idx] - 'a';
        if (children[i] == nullptr) children[i] = new node();

        int res = children[i]->add(s, w, idx + 1);
        if (w > mw) mw = w, mwi = res;
        return res;
    }

    void build(vec<vec<int>> &adj) {
        if (index != 0 && mwi != -1) adj[index].push_back(mwi);
        for (auto ch: children) {
            if (ch == nullptr) continue;

            adj[index].push_back(ch->index);
            adj[ch->index].push_back(index);

            ch->build(adj);
        }
    }

    int min_dist(vec<int> &dist, string &s, int idx = 0) {
        if (idx < s.size()) {
            int res = dist[index] + (int) s.size() - idx;

            auto ch = children[s[idx] - 'a'];
            if (ch != nullptr) res = min(res, ch->min_dist(dist, s, idx + 1));

            return res;
        }

        int res = dist[index] + idx - (int) s.size();
        for (auto ch: children) {
            if (ch == nullptr) continue;
            res = min(res, ch->min_dist(dist, s, idx + 1));
        }

        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    auto trie = new node();
    int w = n;
    rep(i, 0, n) {
        string s;
        cin >> s;
        trie->add(s, w--);
    }

    vec<vec<int>> adj(ind);
    trie->build(adj);

    vec<int> dist(ind, -1);
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    dist[0] = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int cur = p.first, d = p.second;
        for (int next: adj[cur]) {
            if (dist[next] != -1) {
                dist[next] = min(dist[next], d + 1);
                continue;
            }

            q.emplace(next, d + 1);
            dist[next] = d + 1;
        }
    }

    rep(i, 0, m) {
        string s;
        cin >> s;

        cout << trie->min_dist(dist, s) << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
