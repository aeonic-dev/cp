#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = 1000000007;

void solve() {
    string s;
    cin >> s;
    vec<int> nums(26, 0);
    for (auto ch : s) {
        nums[ch - 'A']++;
    }

    int odd = -1;
    rep(i, 0, 26) {
        if (nums[i] % 2 == 1) {
            if (odd != -1) {
                cout << "NO SOLUTION\n";
                return;
            }

            odd = i;
        }
    }

    for (int i = 0; i <= 25; i++) rep(j, 0, nums[i] / 2) cout << (char) ('A' + i);
    if (odd != -1) cout << (char) ('A' + odd);
    for (int i = 25; i >= 0; i--) rep(j, 0, nums[i] / 2) cout << (char) ('A' + i);
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
