#include <string>
#include <vector>
#include <tuple>

using namespace std;

// returns next, matched position, matched length
tuple<vector<int>, int, int> match(string_view pattern, string_view target) {
    int p = pattern.size();
    // if matching pattern[i] fails
    // next test matching should occur at next[i]
    // next[i] == -1 means matching fails, starts again from 0
    vector<int> next(p);
    next[0] = -1;
    int i = 0, j = -1;
    while (i < p - 1) {
        if (j == -1 || pattern[i] == pattern[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    i = 0, j = 0;
    while (i < target.size() && j < p) {
        if (j == -1 || target[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    return {next, i - j, j};
}

#ifdef DEBUG

#include <iostream>

int main() {
    string pattern = "abaaba";
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