#include <iostream>
#include <string>
#include <list>
#include <deque>

using namespace std;

int al;

bool check_front(char T[], int l, const char A[]) {
    if (l + al > 300001) return false;

    for (int i = 0; i < al; ++i) {
        if (A[i] != T[l + i]) return false;
    }
    return true;
}

bool check_back(char T[], int r, const char A[]) {
    if (r < al) return false;

    for (int i = 0; i < al; ++i) {
        if (A[al - 1 - i] != T[r - 1 - i]) return false;
    }
    return true;
}

bool check_back(deque<char> deq, const char A[]) {
    if (deq.size() < al) return false;

    for (int i = 0; i < al; ++i) {
        if (A[al - 1 - i] != deq.back()) return false;
        deq.pop_back();
    }
    return true;
}
bool check_front(deque<char> deq, const char A[]) {
    if (deq.size() < al) return false;

    for (int i = 0; i < al; ++i) {
        if (A[i] != deq.front()) return false;
        deq.pop_front();
    }
    return true;
}

string getResult(char T[], const char A[]) {
    deque<char> left, right;
    bool direction = true; //true - right, false - left
    int l = 0, r = 0;
    while (T[r] != '\0') r++;

    while (l < r) {
        if (direction) {
            if (check_back(left, A)) {
                for (int i = 0; i < al; ++i) {
                    left.pop_back();
                }
                direction = !direction;
            } else {
                left.push_back(T[l++]);
            }
        }
        else {
            if (check_front(right, A)) {
                for (int i = 0; i < al; ++i) {
                    right.pop_front();
                }
                direction = !direction;
            } else {
                right.push_front(T[--r]);
            }
        }
    }

    while (!right.empty() && !left.empty()) {
        if (direction) {
            if (check_back(left, A)) {
                for (int i = 0; i < al; ++i) {
                    left.pop_back();
                }
                direction = !direction;
            } else {
                left.push_back(right.front());
                right.pop_front();
            }
        }
        else {
            if (check_front(right, A)) {
                for (int i = 0; i < al; ++i) {
                    right.pop_front();
                }
                direction = !direction;
            } else {
                right.push_front(left.back());
                left.pop_back();
            }
        }

    }
    while (check_back(left, A)) {
        for (int i = 0; i < al; ++i) {
            left.pop_back();
        }
    }
    while (check_front(right, A)) {
        for (int i = 0; i < al; ++i) {
            right.pop_front();
        }
    }

    string s1(left.begin(), left.end());
    string s2(right.begin(), right.end());
    return s1+s2;
}


int main() {
//    freopen("../input_data/3111.txt", "rt", stdin);
    char T[300001]{0}, A[26]{0};
    cin >> A >> T;

//    int tl = 0;
//    while (T[tl] != '\0') Tdeq.push_back(T[tl++]);
    al = 0;
    while (A[al] != '\0') al++;

    cout << getResult(T, A) << endl;
    return 0;
}