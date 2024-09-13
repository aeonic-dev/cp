#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;;

const int mod = 1'000'000;
void solve() {
    int n;
    cin >> n;
    map<string, int> m;
    rep(i, 0, n) {
        string str;
        cin >> str;
        m[str]++;
    }
    int max = 0;
    map<int, vector<string>> r;
    for (auto &[k, v] : m) {
        r[v].push_back(k);
        max = ::max(max, v);
    }
    sort(all(r[max]));
    for (auto &str : r[max]) cout << str << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}
