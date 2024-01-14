struct node {
    node *children[26]{};
    bool is_valid_word;
    int valid_paths;

    node() : is_valid_word(false), valid_paths(0) {}

    ~node() {
        for (int i = 0; i < 26; i++) delete children[i];
    }

public:
    void add(const string &s) {
        node *cur = this;

        for (int i = 0; i < s.size(); i++) {
            cur->valid_paths++;
            if (cur->children[s[i] - 'a'] == nullptr) cur->children[s[i] - 'a'] = new node();
            cur = cur->children[s[i] - 'a'];
        }

        cur->valid_paths++;
        cur->is_valid_word = true;
    }

    int count_prefix(const string &s) {
        node *cur = this;

        for (int i = 0; i < s.size(); i++) {
            if (cur->children[s[i] - 'a'] == nullptr) return 0;
            cur = cur->children[s[i] - 'a'];
        }

        return cur->valid_paths;
    }

    int count_pairs() {
        if (valid_paths < 2) return 0;
        if (valid_paths == 2) return 1;

        int num = 0;
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) num += children[i]->count_pairs();
        }

        return num;
    }
};

class string_trie {
    node *root;

public:
    string_trie() : root(new node()) {}

    ~string_trie() {
        delete root;
    }

    void add(string s) {
        root->add(s);
    }

    int count_prefix(const string &s) {
        return root->count_prefix(s);
    }

    bool contains(const string &s) {
        return count_prefix(s);
    }
};
