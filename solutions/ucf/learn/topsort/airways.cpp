#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

vi topoSort(const vector<vi> &gr, const vi &indtof, const map<int, int> &ftoind) {
    vi indeg(sz(gr)), ret;
    for (auto &li : gr) for (int x : li) indeg[x]++;
    priority_queue<int, vi, greater<>> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, sz(gr)) if (indeg[i] == 0) q.push(indtof[i]);
    while (!q.empty()) {
        int i = ftoind.at(q.top()); // top() for priority queue
        ret.push_back(i);
        q.pop();
        for (int x : gr[i])
            if (--indeg[x] == 0) q.push(indtof[x]);
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
    int n;
    cin >> n;
    
    vector<tuple<int, int, int>> flights; // {f, u, v}
    map<string, int> strind; // city name to index
    int num_cities = 0;
    
    map<int, int> ftoind; // flight # to index in metagraph
    vi indtof(n); // index to flight number
    
    rep(i, 0, n) {
        string stru, strv;
        int f;
        cin >> stru >> strv >> f;
        
        if (!strind.count(stru)) strind[stru] = num_cities++;
        if (!strind.count(strv)) strind[strv] = num_cities++;
        flights.emplace_back(f, strind[stru], strind[strv]);
        
        ftoind[f] = i;
        indtof[i] = f;
    }
    
    vector<vi> meta(n);
    for (auto [f1, u1, v1] : flights) {
        for (auto [f2, u2, v2] : flights) {
            if (f1 == f2 || v1 != u2) continue;
            meta[ftoind[f1]].push_back(ftoind[f2]);
        }
    }
    
    vi res = topoSort(meta, indtof, ftoind);
    for (int ind : res) cout << indtof[ind] << " ";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
