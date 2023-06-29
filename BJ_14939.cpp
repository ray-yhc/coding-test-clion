#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
int N,M;
bool gMap[11][11];
vector<vector<int>> combinations;
int dr[]{0, -1, 0, 1}, dc[]{1, 0, -1, 0};


void combination(int R, int r, vector<int> list){
    if (r>=R ) {
        combinations.push_back(list);
        return;
    }
    // r 미포함
    combination(R, r+1,  list);
    // r 포함
    list.emplace_back(r);
    combination(R, r+1,  list);
}

void controlSwitch(int r, int c, bool map[][11]){
    map[r][c] = !map[r][c];
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr <0||nr>=N||nc<0||nc>=M) continue;
        map[nr][nc] = !map[nr][nc];
    }
}

int countSwitches(int N, int M){
    int count = 100 * 100 + 1;

    // 조합 만들고
    vector<int> temp;
    combination(N,0,temp);

    // 하나씩 실행
    for (auto com: combinations) {
        // init
        bool tMap[11][11];
        memcpy(tMap, gMap, sizeof(bool) * 11 * 11);
        int tCount = 0;

        // set
        for (int c: com) {
            int r = 0;
            tCount++;
            controlSwitch(r, c, tMap);
        }

        for (int r = 1; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (tMap[r-1][c]) {
                    tCount++;
                    controlSwitch(r, c,tMap);
                }
            }
        }

        // 검사
        int r = N - 1;
        bool checked = true;
        for (int c = 0; c < M; ++c) {
            if (tMap[r][c]) {
                checked = false;
            }
        }

        if (checked) {
            count = (count > tCount) ? tCount : count;
        }
    }

    return (count == 100 * 100 + 1) ? -1 : count;
}

int main() {
    N = 10;
    M = 10;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char cc;
            cin >> cc;
            gMap[i][j] = (cc == 'O');
        }
    }

    cout << countSwitches(N, M);
    return 0;
}
