#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

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

//void printMeeting(vector<int> mbs) {
//    for (auto mb: mbs) {
//        cout << mb << " ";
//    }
//    cout << ": ";
//}

void spread(const bool from[100001], bool to[100001]) {
    // initial에 있는 member들을 result에 memcpy
    for (int i = 1; i <= N; ++i) {
        if (from[i]) {
            to[i] = true;
        }
    }


    for (auto mbs: meets) {
//        printMeeting(mbs);
        // 한명이라도 initial에 있으면
        bool isInitial = false;
        for (auto mb: mbs) {
            if (to[mb]) {
                isInitial = true;
                break;
            }
        }

        // result의 모든 member true
        if (isInitial) {
            for (auto mb: mbs) {
                to[mb] = true;
            }
//            printList(to);
        }
    }
}


void search() {
    for (int i = 1; i <= N; ++i) {
        initial[i] = result[i];
    }

    for (int i = meets.size() -1 ; i >=0 ; i--) {
        // 한명이라도 확진이 아니라면
        bool isTrue = true;
        for (auto m: meets[i]) {
            if (!initial[m]) {
                isTrue = false;
                break;
            }
        }

        // 모두 확진 x
        if (!isTrue) {
            for (auto m: meets[i]) {
                initial[m] = false;
            }
        }
    }
}

bool isAllFalse (bool list[100001]) {
    bool existTrue = false;
    for (int i = 1; i <=N ; ++i) {
        if (list[i]) {
            existTrue = true;
            break;
        }
    }
    return !existTrue;
}


bool check() {
    // initial이 모두 false이면 return false
    if (isAllFalse(initial)) {
        return false;
    }

    // 실행했을 때 결과와 다르면 return false
    bool tempRes[100001];
    spread(initial, tempRes);
    for (int i =1; i <=N ; ++i) {
        if (tempRes[i] != result[i]) {
            return false;
        }
    }
    return true;
}

void doit() {
    cin >> N >> M;

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

    for (int i = 1; i <= N; ++i) {
        int t;
        cin >> t;
        result[i] = t;
    }

    if(isAllFalse(result)){
        cout<< "YES" << endl;
        printList(result);
        return ;
    }

    search();

    if (check()) {
        cout<< "YES" << endl;
        printList(initial);
    } else cout << "NO" << endl;
}

int main() {
    doit();
    return 0;
}


//5 3
//3 2 3 4
//3 1 2 3
//4 2 3 4 5
//0 1 1 1 1
//answer : 0 0 0 0 1
//
//5 3
//2 1 2
//2 4 5
//3 2 3 4
//0 0 0 1 1
//answer : NO
//
//5 3
//2 1 2
//3 2 3 4
//2 4 5
//0 0 0 1 1
//answer : 0 0 0 0 1