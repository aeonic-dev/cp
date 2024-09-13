#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

void solve() {
    string str;
	int tc = 0;
    while (cin >> str, str != "end") {
        set<char> stacks;
        ll res = 0;
        for (char ch : str) {
            if (stacks.count(ch)) continue;
            for (char st = ch + 1; st <= 'Z'; st++) {
                if (!stacks.count(st)) continue;
                stacks.erase(st), stacks.insert(ch);
                goto next;
            }
			stacks.insert(ch);
            res++;
        next:;
        }
		cout << "Case " << ++tc << ": ";
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
