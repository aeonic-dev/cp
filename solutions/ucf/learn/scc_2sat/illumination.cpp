#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct TwoSat {
    int N;
    vector<vi> gr;
    vi values; // 0 = false, 1 = true
    
    TwoSat(int n = 0) : N(n), gr(2 * n) {}
    
    int addVar() { // (optional)
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }
    
    void either(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }
    void setValue(int x) { either(x, x); }
    
    void atMostOne(const vi &li) { // (optional)
        if (sz(li) <= 1) return;
        int cur = ~li[0];
        rep(i, 2, sz(li)) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }
    
    vi val, comp, z;
    int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (int e : gr[i])
            if (!comp[e])
                low = min(low, val[e] ?: dfs(e));
        if (low == val[i])
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1)
                    values[x >> 1] = x & 1;
            } while (x != i);
        return val[i] = low;
    }
    
    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        rep(i, 0, 2 * N) if (!comp[i]) dfs(i);
        rep(i, 0, N) if (comp[2 * i] == comp[2 * i + 1]) return 0;
        return 1;
    }
};

void solve() {
    int n, r, k;
    cin >> n >> r >> k;
    vector<vector<vi>> litbyr(n, vector<vi>(n)),
            litbyc(n, vector<vi>(n));
    
    rep(lamp, 0, k) {
        int row, col;
        cin >> row >> col, row--, col--;
        rep(i, max(0, row - r), min(n, row + r + 1)) {
            litbyc[i][col].push_back(lamp * 2 + 1);
        }
        rep(j, max(0, col - r), min(n, col + r + 1)) {
            litbyr[row][j].push_back(lamp * 2);
        }
    }
    
    // i * 2 = illuminate row, i * 2 + 1 = illuminate col
    TwoSat ts(k * 2);
    rep(l, 0, k) ts.either(l * 2, l * 2 + 1);
    rep(i, 0, n) {
        rep(j, 0, n) {
            ts.atMostOne(litbyr[i][j]);
            ts.atMostOne(litbyc[i][j]);
        }
    }
    cout << ts.solve() << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}
