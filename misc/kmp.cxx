#include <string>
#include <vector>
#include <tuple>

using namespace std;

// returns next, matched position, matched length
tuple<vector<int>, int, int> match(string_view pattern, string_view target) {
    int p = pattern.size();
    int t = target.size();
    // next[i] is the length of the longest prefix of pattern[0, i] that is also a suffix of pattern[0, i]
    // when matching pattern[j] fails, j should jump to next[j - 1], where the next match occurs
    vector<int> next(p, 0);
    for(int i = 1, j = 0; i < p; ++i) {
        while(j > 0 && pattern[i] != pattern[j]) j = next[j - 1];
        if (pattern[i] == pattern[j]) ++j;
        next[i] = j;
    }
    for(int i = 0, j = 0; i < t; ++i) {
        while(j > 0 && target[i] != pattern[j]) j = next[j - 1];
        if (target[i] == pattern[j]) ++j;
        if (j == p) return {next, i - p + 1, p};
    }
    return {next, -1, 0};
}

#ifdef DEBUG

#include <iostream>

int main() {
    string pattern = "abaabab";
    string target = "aaababaaba";
    auto [next, pos, len] = match(pattern, target);
    cout << "next: ";
    for (auto x : next) {
        cout << x << " ";
    }
    cout << endl;
    cout << "pos: " << pos << endl;
    cout << "len: " << len << endl;
    return 0;
}

#endif