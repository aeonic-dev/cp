#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<vi>> f(n, vector<vi>(n, vi(26, 0)));
    vector<vector<stack<int>>> st(n, vector<stack<int>>(n));
    rep(i, 0, m) {
        int q, x, y;
        cin >> q;
        
        if (q == 0) {
            char ch;
            cin >> ch >> x >> y;
            int v = ch - 'a';
            
            f[y][x][v]++;
            st[y][x].push(v);
            continue;
        }
        
        if (q == 1) {
            cin >> x >> y;
            
            if (st[y][x].empty()) continue;
            f[y][x][st[y][x].top()]--;
            st[y][x].pop();
            continue;
        }
        
        char ch;
        cin >> ch >> x >> y;
        int v = ch - 'a';
        
        int ft = accumulate(all(f[y][x]), 0);
        int fv = f[y][x][v];
        if (fv > ft / 2) cout << "yes\n";
        else cout << "no\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}
