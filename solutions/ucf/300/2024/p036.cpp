#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                    jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi> &C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi> &C, int v, int par) {
        time[v] = T++;
        for (int y : C[v])
            if (y != par) {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v);
            }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

void solve() {
    int k, q;
    cin >> k >> q;
    int n = 1 << k;
    map<string, int> ids;
    vector<pair<int, int>> games((1 << k) - 1);
    vi num_wins(n, 0);
    rep(i, 0, (1 << k) - 1) {
        string a, b, tmp;
        int a_g, a_p, b_g, b_p;

        cin >> a >> tmp;
        if (count(all(tmp), '(')) {
            a_g = stoi(tmp.substr(0, tmp.find('(')));
            a_p = stoi(tmp.substr(tmp.find('(') + 1, sz(tmp) - 1));
            cin >> tmp >> tmp >> b;
            b_g = stoi(tmp.substr(0, tmp.find('(')));
            b_p = stoi(tmp.substr(tmp.find('(') + 1, sz(tmp) - 1));

            if (!ids.count(a)) ids[a] = sz(ids);
            if (!ids.count(b)) ids[b] = sz(ids);

            if (a_p > b_p) games[i] = {ids[a], ids[b]};
            else games[i] = {ids[b], ids[a]};
            num_wins[games[i].first]++;
            continue;
        }

        a_g = stoi(tmp);
        cin >> tmp >> b_g >> b;

        if (!ids.count(a)) ids[a] = sz(ids);
        if (!ids.count(b)) ids[b] = sz(ids);

        if (a_g > b_g) games[i] = {ids[a], ids[b]};
        else games[i] = {ids[b], ids[a]};
        num_wins[games[i].first]++;
    }

    vector<map<int, int>> mp(n); // [u][# wins for v] -> v
    for (auto [a, b] : games) mp[a][num_wins[b]] = b;

    // rep(u, 0, n) {
    //     cout << u << " -> {" << "\n "[num_wins[u] == 0];
    //     for (auto [w, v] : mp[u]) cout << "\t" << w << " : " << v << "\n";
    //     cout << "}\n";
    // }

    // for (auto [k, v] : ids) cout << k << " -> " << v << "\n";
    // for (auto [a, b] : games) cout << a << " beat " << b << "\n";
    // rep(i, 0, n) cout << i << " has " << num_wins[i] << " wins\n";
    // cout << a << " vs " << b << "\n";

    vi pos(n, -1); // position of team i in [0, n)
    // winner, # of opponent's wins, index of winner
    auto go = [&](int a, int w, int l, auto &go) -> void {
        if (w == -1) return void(pos[a] = l);
        int b = mp[a][w];
        int r = l + (1 << w);
        go(a, w - 1, l, go);
        go(b, w - 1, r, go);
    };

    int top; // overall winner
    rep(i, 0, n) if (num_wins[i] == k) top = i;
    go(top, k - 1, 0, go);

    // cout << "\npos = {\n";
    // rep(i, 0, n) {
    //     string t;
    //     for (auto [k, v] : ids)
    //         if (v == pos[i]) t = k;
    //     cout << "  " << t << ",\n";
    // }
    // cout << "}\n\n";

    rep(i, 0, q) {
        string stra, strb;
        cin >> stra >> strb;
        int a = ids[stra], b = ids[strb];
        int res = 1, p2 = 2;
        while (pos[a] / p2 != pos[b] / p2) res++, p2 *= 2;
        // int d = abs(pos[b] - pos[a]), res = 1;
        // cout << "pos[a], pos[b] -> " << pos[a] << ", " << pos[b] << "\n";
        // while (d >>= 1) res++;
        cout << res << "\n";
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
