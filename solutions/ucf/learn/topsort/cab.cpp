#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

vi topoSort(const vector<vi> &gr) {
    vi indeg(sz(gr)), ret;
    for (auto &li : gr) for (int x : li) indeg[x]++;
    queue<int> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, sz(gr)) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int i = q.front(); // top() for priority queue
        ret.push_back(i);
        q.pop();
        for (int x : gr[i])
            if (--indeg[x] == 0) q.push(x);
    }
    return ret;
}

// at most one relation can be inferred from a pair of words
pair<int, int> get_rltn(const string &a, const string &b) {
    if (a == b) return {-1, -1};
    rep(i, 0, max(sz(a), sz(b))) {
        if (i == sz(a)) return {-1, -1}; // a is a prefix of b (?)
        if (i == sz(b)) return {-2, -2}; // no valid ordering
        if (a[i] != b[i]) return {(int) a[i] - 'a', (int) b[i] - 'a'};
    }
    return {-1, -1}; // shouldn't get to here, i think
}

void solve() {
    int m;
    string lstr;
    cin >> lstr >> m;
    
    vector<string> words(m);
    for (auto &str : words) cin >> str;
    
    int n = (int) lstr[0] - '`'; // - 'a' + 1
    vector<vi> adj(n);
    rep(w, 1, m) {
        auto [u, v] = get_rltn(words[w - 1], words[w]);
//        cout << (char)(u + 'a') << "->" << (char)(v + 'a') << "\n";
        if (u == -2) return void(cout << "1\n");// inconsistent
        if (u == v) continue; // no relation can be inferred
        
        adj[u].push_back(v);
    }
    
    vi res = topoSort(adj);
    if (sz(res) < n) {
        cout << "1\n";
        return;
    }
    
    rep(i, 1, n) {
        int u = res[i - 1], v = res[i];
        if (!count(all(adj[u]), v)) {
            cout << "0\n";
            return;
        }
    }
    for (int x : res) cout << (char) (x + 'a');
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}
