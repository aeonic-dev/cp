void unset_bit(ll &mask, int i) {
    mask &= ~(1 << i);
}

void set_bit(ll &mask, int i, bool val = true) {
    if (val) mask |= (1 << i);
    else unset_bit(mask, i);
}

bool get_bit(ll &mask, int i) {
    return (mask >> i) & 1;
}

bool flip_bit(ll &mask, int i) {
    mask ^= (1 << i);
    return get_bit(mask, i);
}