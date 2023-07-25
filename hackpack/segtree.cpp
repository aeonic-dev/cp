struct node_data {
    bool lazy;
    int lazy_lo, lazy_hi;
};

struct node {
    // Node data container type
    typedef node_data data_t;

    int lo, hi; // Node range (inclusive, 1-indexed)
    node *left, *right; // Children
    data_t data; // Node data container

    node(int lo, int hi) : lo(lo), hi(hi) {
        if (is_leaf()) make_leaf(lo);
        else {
            left = new node(lo, (lo + hi) / 2);
            right = new node((lo + hi) / 2 + 1, hi);

            merge(left->data, right->data);
        }
    }

    ~node() {
        if (is_leaf()) return;

        delete left;
        delete right;
    }

    // Whether this is a leaf node (only spans one index)
    bool is_leaf() {
        return lo == hi;
    }

    // Number of indices in this node's purview
    int width() {
        return hi - lo + 1;
    }

    // Propagates updates to children and recomputes data for this node
    void push() {
        if (is_leaf() || !data.lazy) return;

        // Push lazy update to children
        left->do_thing(data.lazy_lo, data.lazy_hi);
        right->do_thing(data.lazy_lo, data.lazy_hi);

        // Recompute data from children's new state
        merge(left->data, right->data);

        // Reset lazy flags
        data.lazy = false;
        data.lazy_lo = data.lazy_hi = -1;
    }

    void do_thing(int l, int r) {
        if (l > hi || r < lo) return;

        if (l <= lo && r >= hi) {
            // Full cover: lazy update
            // TODO: Do something
        }

        // Partial cover: update children now and recompute values
        push();

        // Partial cover implies this is not a leaf node, so we don't need extra checks here
        left->do_thing(l, r);
        right->do_thing(l, r);

        // Update data from new state of children
        merge(left->data, right->data);
    }

    // Initializes the data container for a leaf node (lo = hi)
    void make_leaf(int i) {
        // TODO: Set up leaf data
    }

    // Recomputes the data container for a node from its children's data
    // (after lazy updates are pushed)
    void merge(const data_t &l, const data_t &r) {
        // TODO: Compute data from children
    }
};