#include <vector>
#include <string>
#include <functional>

using namespace std;

struct Node {
    vector<Node*> children;
    char val;
    bool isEnd;
    Node() : children(26, nullptr), val('\0'), isEnd(false) {}
    Node(char val, bool isEnd=false): children(26, nullptr), val(val), isEnd(isEnd) {}
};

struct Trie {
    Node *root;
    size_t size;
    Trie() : root(new Node()), size(0) {}
    
    void insert(string_view s) {
        Node *cur = root;
        for (char c : s) {
            if (cur->children[c - 'a'] == nullptr) cur->children[c - 'a'] = new Node(c);
            cur = cur->children[c - 'a'];
        }
        cur->isEnd = true;
        ++size;
    }

    bool find(string_view s) {
        Node *cur = root;
        for (char c : s) {
            if (cur->children[c - 'a'] == nullptr) return false;
            cur = cur->children[c - 'a'];
        }
        return cur->isEnd;
    }

    void erase(string_view s) {
        Node *cur = root;
        for (char c : s) {
            if (cur->children[c - 'a'] == nullptr) return;
            cur = cur->children[c - 'a'];
        }
        cur->isEnd = false;
        --size;
    }

    vector<string> starts_with(string_view prefix) {
        vector<string> res;
        Node *cur = root;
        for (char c : prefix) {
            if (cur->children[c - 'a'] == nullptr) return res;
            cur = cur->children[c - 'a'];
        }
        string stk = string(prefix.data());
        function<void(Node*)> dfs = [&](Node *cur) {
            if (cur->isEnd) res.push_back(stk);
            for (int i = 0; i < 26; ++i) {
                if (cur->children[i] != nullptr) {
                    stk.push_back('a' + i);
                    dfs(cur->children[i]);
                    stk.pop_back();
                }
            }
        };
        dfs(cur);
        return res;
    }
};

#ifdef DEBUG

#include <iostream>

int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hell");
    trie.insert("word");
    cout << trie.find("hello") << endl;
    cout << trie.find("hell") << endl;
    cout << trie.find("hey") << endl;
    vector<string> res = trie.starts_with("w");
    for (string_view s : res) cout << s << endl;
    return 0;
}

#endif