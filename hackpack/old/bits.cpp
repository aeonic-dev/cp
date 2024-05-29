template<typename n_t>
void unset_bit(n_t &mask, int i) {
    mask &= ~(1 << i);
}

template<typename n_t>
void set_bit(n_t &mask, int i, bool val = true) {
    if (val) mask |= (1 << i);
    else unset_bit(mask, i);
}

template<typename n_t>
bool get_bit(n_t &mask, int i) {
    return (mask >> i) & 1;
}

template<typename n_t>
bool flip_bit(n_t &mask, int i) {
    mask ^= (1 << i);
    return get_bit(mask, i);
}

// Counts bits via Kernighan's algorithm
// https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
template<typename n_t>
int count_bits_set(n_t mask) {
    int count;
    for (count = 0; mask; count++) {
        mask &= mask - 1;
    }

    return count;
}