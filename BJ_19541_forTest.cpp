#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

bool member[100001]{false};
bool initial[100001]{false};
bool result[100001]{false};
int N, M;
vector<vector<int>> meets;


void printList(bool list[100001]) {
    for (int i = 1; i <= N; ++i) {
        cout << list[i] << " ";
    }
    cout << endl;
}

void printMeeting(vector<int> mbs) {
    for (auto mb: mbs) {
        cout << mb << " ";
    }
    cout << ": ";
}

void spread() {
    // initial에 있는 member들을 result에 memcpy
    for (int i = 1; i <= N; ++i) {
        if (initial[i]) {
            result[i] = true;
        }
    }


    for (auto mbs: meets) {
        printMeeting(mbs);
        // 한명이라도 initial에 있으면
        bool isInitial = false;
        for (auto mb: mbs) {
            if (result[mb]) {
                isInitial = true;
                break;
            }
        }

        // result의 모든 member true
        if (isInitial) {
            for (auto mb: mbs) {
                result[mb] = true;
            }
            printList(result);
        } else cout << endl;
    }
}

int doit() {
    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        int t;
        cin >> t;
        initial[i] = t;
    }

    for (int i = 1; i <= N; ++i) {
        cout << initial[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < M; ++i) {
        int k;
        cin >> k;
        // meets에 새로운 빈 vector 추가
        meets.emplace_back();
        for (int j = 0; j < k; ++j) {
            int m;
            cin >> m;
            // 새로 생성한 vector에 참석자 추가
            meets[i].push_back(m);
        }
    }

    spread();

    for (int i = 1; i <= N; ++i) {
//        int t;
//        cin >> t;
//        result[i] = t;
        cout << result[i] << " ";
    }
}

int main() {
    freopen("../input_data/19541.txt", "rt", stdin);

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        cout << endl << t << " ==================================" << endl;
        doit();

        //init initial, result, meets
        for (int i = 0; i < 100001; ++i) {
            initial[i] = false;
            result[i] = false;
        }
        while (!meets.empty()) {
            meets.pop_back();
        }
    }

    return 0;
}
