#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
	int n, a, b;
	cin >> n >> a >> b;

	// {distance, team, 0/1=a/b}
	priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<>> pq;
	vi left(n); // # of balloons each team still needs
	rep(i, 0, n) {
		int da, db;
		cin >> left[i] >> da >> db;
		pq.emplace(da, i, 0);
		pq.emplace(db, i, 1);
	}

	ll res = 0;
	while (!pq.empty()) {
		auto [d, i, w] = pq.top();
		pq.pop();
		if (!left[i]) continue;

		if (w == 0 && a) {
			ll num = min(a, left[i]);
			res += num * d;
			left[i] -= num;
			a -= num;
		}
		if (w == 1 && b) {
			ll num = min(b, left[i]);
			res += num * d;
			left[i] -= num;
			b -= num;
		}
	}
	cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
