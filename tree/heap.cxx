#include <vector>
#include <functional>

using namespace std;

struct Heap {
    vector<int> data;
    function<bool(int, int)> cmp;
    Heap(function<bool(int, int)> cmp) : cmp(cmp) {}
    void set_data(vector<int> raw) {
        this->data = raw;
        // now, heapify the data
        function<void(int)> make_heap = [&](int i) {
            int next = i;
            // choose the child that is smaller than the parent
            if (2 * i + 1 < data.size() && cmp(data[2 * i + 1], data[next])) next = 2 * i + 1;
            if (2 * i + 2 < data.size() && cmp(data[2 * i + 2], data[next])) next = 2 * i + 2;
            if (i == next) return;
            swap(data[i], data[next]);
            make_heap(next);
        };
        for(int i = data.size() - 1; i >= 0; --i) make_heap(i);
    }
    void push(int val) {
        data.push_back(val);
        // now, the new val is at the bottom of the heap
        // we need to move it up to the correct postion
        // the parent of the node at index i is (i - 1) / 2
        // e.g. the parent of the node at index 1 is 0 / 2 = 0
        // e.g. the parent of the node at index 2 is 1 / 2 = 0
        for(int i = data.size() - 1; i > 0; i = (i - 1) / 2) {
            if (cmp(data[i], data[(i - 1) / 2])) swap(data[i], data[(i - 1) / 2]);
            else break;
        }
    }
    int pop() {
        int res = data[0];
        data[0] = data.back();
        data.pop_back();
        // now move the top node down to the correct position
        // the children of the node at index i are 2 * i + 1 and 2 * i + 2
        // e.g. the children of the node at index 0 are 1 and 2
        for(int i = 0; i < data.size(); ) {
            int next = i;
            // choose the child that is smaller than the parent
            if (2 * i + 1 < data.size() && cmp(data[2 * i + 1], data[next])) next = 2 * i + 1;
            if (2 * i + 2 < data.size() && cmp(data[2 * i + 2], data[next])) next = 2 * i + 2;
            if (i == next) break;
            swap(data[i], data[next]);
            i = next;
        }
        return res;
    }
    int top() {
        return data[0];
    }
    int size() {
        return data.size();
    }
    bool empty() {
        return data.empty();
    }
};

#ifdef DEBUG

#include <iostream>

int main() {
    Heap heap([&](int a, int b) { return a < b; });
    vector<int> d = { -1, 9, 8, 7, 6, 4, 5 };
    for(auto e: d) heap.push(e);
    while(!heap.empty()) cout << heap.pop() << " ";
    return 0;
}

#endif