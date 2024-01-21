const ll base = 30;
const ll mod = 1e9 + 7;

vec<ll> pwr;
string s;

struct node {
    int lo, hi, len;
    node *left, *right;
    ll ltor, rtol;

    node(int lo, int hi) : lo(lo), hi(hi), len(hi - lo + 1) {
        if (lo == hi) {
            ltor = rtol = s[lo] - 'a' + 1;
            return;
        }

        left = new node(lo, (lo + hi) / 2);
        right = new node((lo + hi) / 2 + 1, hi);
        merge();
    }

    void merge() {
        ltor = (((left->ltor * pwr[right->len]) % mod) + right->ltor) % mod;
        rtol = (((right->rtol * pwr[left->len]) % mod) + left->rtol) % mod;
    }

    void set(int ind, char ch) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) {
            s[ind] = ch; // ind = lo
            ltor = rtol = s[ind] - 'a' + 1;
            return;
        }

        left->set(ind, ch), right->set(ind, ch);
        merge();
    }

    pair<ll, ll> get_ltor(int l, int r) {
        if (l > hi || r < lo) return {0, 0};
        if (l <= lo && r >= hi) return {ltor, len};

        auto resl = left->get_ltor(l, r);
        auto resr = right->get_ltor(l, r);

        return {
                ((resl.first * pwr[resr.second]) % mod + resr.first) % mod,
                resl.second + resr.second
        };
    }

    pair<ll, ll> get_rtol(int l, int r) {
        if (l > hi || r < lo) return {0, 0};
        if (l <= lo && r >= hi) return {rtol, len};

        auto resl = left->get_rtol(l, r);
        auto resr = right->get_rtol(l, r);

        return {
                ((resr.first * pwr[resl.second]) % mod + resl.first) % mod,
                resl.second + resr.second
        };
    }

    bool is_palindrome(int l, int r) {
        auto resltor = get_ltor(l, r);
        auto resrtol = get_rtol(l, r);

        return resltor.first == resrtol.first;
    }
};
