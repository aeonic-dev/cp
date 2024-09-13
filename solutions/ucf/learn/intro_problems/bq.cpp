#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, s;
    cin >> n >> s;
    
    map<string, int> mins;
    rep(i, 0, n) {
        string str;
        cin >> str;
        mins[str] = INT_MAX;
    }
    rep(t, 1, s + 1) {
        string str;
        cin >> str;
        mins[str] = min(mins[str], t);
    }
    
    vector<pair<int, string>> res;
    for (auto [str, min] : mins)
        res.emplace_back(min, str);
    sort(all(res));
    cout << res.back().second << " " << res[sz(res) - 2].first << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
