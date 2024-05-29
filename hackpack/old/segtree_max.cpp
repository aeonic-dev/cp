struct node {
    int l_i, r_i;
    long long lazy, max;
    node *left, *right;

    node(int l, int r) : l_i(l), r_i(r), lazy(0), max(0), left(nullptr), right(nullptr) {}

    ~node() {
        delete left;
        delete right;
    }

    void increment(int l, int r, int amt);

    void push();

    long long get_max();
};

void node::increment(int l, int r, int amt) {
    if (l > r_i || r < l_i) return;
    if (l <= l_i && r >= r_i) {
        lazy += amt;
        max += amt;
        return;
    }

    push();
    left->increment(l, r, amt);
    right->increment(l, r, amt);
    max = std::max(left->max, right->max);
}

void node::push() {
    if (left == nullptr) left = new node(l_i, (l_i + r_i) / 2);
    if (right == nullptr) right = new node((l_i + r_i) / 2 + 1, r_i);

    if (lazy != 0) {
        left->increment(l_i, r_i, lazy);
        right->increment(l_i, r_i, lazy);
        lazy = 0;
    }
}

long long node::get_max() {
    push();
    return max;
}