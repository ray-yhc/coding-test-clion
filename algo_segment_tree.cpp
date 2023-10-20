#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr size_t n = 5;

int a[n] = {5, -1, 3, 2, -8};
int segtree[2 * n];

//void init() {
//    for (size_t i = 0; i < n; ++i) {
//        segtree[i + n] = a[i];
//    }
//    for (size_t i = n - 1; i != 0; --i) {
//        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
//    }
//}

void init() {
    for (int i = 0; i < n; ++i) {
        segtree[n + i] = a[i];
    }
    for (int i = n - 1; i > 0; --i) {
        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1]; // parent = left + right
    }
}

void update(size_t i, int x) {
    segtree[i += n] = x;
    while (i>>=1) {
        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
    }
}

int query(size_t l, size_t r) {
    int result = 0;
    for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
        if (l & 1) result += segtree[l++];
        if (r & 1) result += segtree[--r];
    }
    return result;
}

int query(int l, int r){
    int result = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) result += segtree[l++];
        if (r & 1) result += segtree[--r];
    }
}

int main() {

    vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin();
    for (int k = 0; k < 5; ++k) {
        cout << *it << endl;
        it=v.erase(it);
//        it++;
    }
    v = {1, 2, 3, 4, 5};
    std::remove(v.begin(), v.end(), 3);
    v.erase(remove(v.begin(),v.end(),4),v.end());
    v.erase(v.begin() + 2, v.end());

    return 0;
}