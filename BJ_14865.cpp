#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;


int main() {
//    freopen("../input_data/3111.txt", "rt", stdin);

    priority_queue<int> zeros;
    unordered_map<int, int> mountain; // {right, left}

    int N;
    cin >> N;


    queue<pair<int, int>> queue;
    int r, c, rp, cp, mc1, mc2;
    int n = N;
//    bool isMountain = false;
    bool started = false;
    for (int i = 0; i <= N; ++i) {
        if (i == 0){
            cin >> c >> r;
            queue.emplace(c, r);
            continue;
        }
        else if (i < n)
            cin >> c >> r;
        else {
            c = queue.front().first;
            r = queue.front().second;
            queue.pop();
        }

        if (!started) {
            queue.emplace(c, r);
            N++;
            if (r > 0) {
                continue;
            } else started = true;
        }

        // 가로세로 탐지
        if (c == cp) {
            if (r > 0 && rp <= 0) { // 봉우리 시작
                mc1 = c;
//                isMountain = true;
            } else if (rp > 0 && r <= 0) { // 봉우리 끝
                mc2 = c;
                zeros.push(mc1);
                zeros.push(mc2);

                if (mc1 < mc2) {
                    mountain[mc2] = mc1;
                } else {
                    mountain[mc1] = mc2;
                }
//                isMountain = false;
            }
        }
        //
        rp = r;
        cp = c;
    }

    int lowest = 0, highest = 0;
    cp = 0;
    stack<pair<int, int>> stack;
    while (!zeros.empty()) {
        c = zeros.top();
        zeros.pop();

        if (stack.empty() || stack.top().second != c) {
            stack.emplace(c, mountain[c]);
        } else if (stack.top().second == c) {
            stack.pop();
            if (mountain.find(cp) != mountain.end() && mountain.find(cp)->second == c)lowest++;
            if (stack.empty()) highest++;
        }
        cp = c;
    }


    cout << highest << " " << lowest << endl;
    return 0;
}

//17
//5 -1
//5 5
//12 5
//12 -1
//11 -1
//11 4
//6 4
//6 -1
//7 -1
//7 4
//8 4
//8 -1
//9 -1
//9 4
//10 4
//10 -3
//5 -3