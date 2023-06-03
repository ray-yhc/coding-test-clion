#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int R, C;
int map[21][21]{0};
vector<pair<pair<int, int>, int>> heaters;
vector<pair<int, int>> thermometers;


bool rw[21][21]{false}, lw[21][21]{false}, uw[21][21]{false}, dw[21][21]{false};

void printMap() {
    cout << "===========================" << endl;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << "===========================" << endl;
}

void heat_iter(int tempMap[][21], int r, int c, int dir, int depth) {
    if (depth == 0) return;
    if (r < 0 || r >= R || c < 0 || c >= C) return;
    if (tempMap[r][c] != 0) return;

    tempMap[r][c] = depth;

    // 진행시 wall 확인
    switch (dir) {
        case 1: // r
            if (!rw[r][c])
                heat_iter(tempMap, r, c + 1, dir, depth - 1);
            if (!uw[r][c] &&
                !(r - 1 < 0 || r - 1 >= R) &&
                !rw[r - 1][c])
                heat_iter(tempMap, r - 1, c + 1, dir, depth - 1);
            if (!dw[r][c] &&
                !(r + 1 < 0 || r + 1 >= R) &&
                !rw[r + 1][c])
                heat_iter(tempMap, r + 1, c + 1, dir, depth - 1);
            break;
        case 2: // l
            if (!lw[r][c])
                heat_iter(tempMap, r, c - 1, dir, depth - 1);

            if (!uw[r][c] &&
                !(r - 1 < 0 || r - 1 >= R) &&
                !lw[r - 1][c])
                heat_iter(tempMap, r - 1, c - 1, dir, depth - 1);
            if (!dw[r][c] &&
                !(r + 1 < 0 || r + 1 >= R) &&
                !lw[r + 1][c])
                heat_iter(tempMap, r + 1, c - 1, dir, depth - 1);
            break;
        case 3: // u
            if (!uw[r][c])
                heat_iter(tempMap, r - 1, c, dir, depth - 1);
            if (!lw[r][c] &&
                !(c - 1 < 0 || c - 1 >= C) &&
                !uw[r][c - 1])
                heat_iter(tempMap, r - 1, c - 1, dir, depth - 1);
            if (!rw[r][c] &&
                !(c + 1 < 0 || c + 1 >= C) &&
                !uw[r][c + 1])
                heat_iter(tempMap, r - 1, c + 1, dir, depth - 1);
            break;
        case 4: // d
            if (!dw[r][c])
                heat_iter(tempMap, r + 1, c, dir, depth - 1);
            if (!lw[r][c] &&
            !(c - 1 < 0 || c - 1 >= C) &&
            !dw[r][c - 1])
                heat_iter(tempMap, r + 1, c - 1, dir, depth - 1);
            if (!rw[r][c] &&
            !(c + 1 < 0 || c + 1 >= C) &&
            !dw[r][c + 1])
                heat_iter(tempMap, r + 1, c + 1, dir, depth - 1);
            break;
        default:
            break;
    }
}

void heat(int r, int c, int dir) {
    int tempMap[21][21]{0};
    // 시작점부터 iteration
    switch (dir) {
        case 1: // r
            if (!rw[r][c]) {
                heat_iter(tempMap, r, c + 1, dir, 5);
            }
            break;
        case 2: // l
            if (!lw[r][c]) {
                heat_iter(tempMap, r, c - 1, dir, 5);
            }
            break;
        case 3: // u
            if (!uw[r][c]) {
                heat_iter(tempMap, r - 1, c, dir, 5);
            }
            break;
        case 4: // d
            if (!dw[r][c]) {
                heat_iter(tempMap, r + 1, c, dir, 5);
            }
            break;
        default:
            break;
    }


    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            map[i][j] += tempMap[i][j];
        }
    }
}

void balance() {
    int dc[2]{1, 0};
    int dr[2]{0, 1};

    int mapDiff[21][21]{0};

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            for (int k = 0; k < 2; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

                // 벽 체크
                if (k == 0 && rw[r][c])// r
                    continue;
                else if (k == 1 && dw[r][c]) // d
                    continue;

                // 가감치 계산
                int diff = (map[r][c] - map[nr][nc]) / 4;
                mapDiff[r][c] -= diff;
                mapDiff[nr][nc] += diff;
            }
        }
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            map[i][j] += mapDiff[i][j];
        }
    }

}

void reduction() {
    int i = 0, j = 0;
    for (j = 0; j < C; ++j) {
        map[i][j] = (map[i][j] != 0) ? map[i][j] - 1 : 0;
    }
    i = R - 1;
    for (j = 0; j < C; ++j) {
        map[i][j] = (map[i][j] != 0) ? map[i][j] - 1 : 0;
    }

    j = 0;
    for (i = 1; i < R - 1; ++i) {
        map[i][j] = (map[i][j] != 0) ? map[i][j] - 1 : 0;
    }
    j = C - 1;
    for (i = 1; i < R - 1; ++i) {
        map[i][j] = (map[i][j] != 0) ? map[i][j] - 1 : 0;
    }
}

bool testK(int K) {
    for (auto t: thermometers) {
        if (map[t.first][t.second] < K) return false;
    }
    return true;
}

int getResult(int K) {
    int choco = 0;
    while (true) {
        // 각 온풍기에서 바람이 나온다.
        for (auto h: heaters) {
            heat(h.first.first, h.first.second, h.second);
        }

//        cout<<(choco+1)<<"================================================"<<endl;
//        printMap();
        // 온도가 조절된다.
        balance();
//        printMap();
        // 온도가 감소된다.
        reduction();
//        printMap();
        // 초콜릿을 먹는다
        choco++;
        // 검사한다.
        if (testK(K)) return choco;
        if (choco >= 100) return 101;
    }
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);
    int K;
    cin >> R >> C >> K;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            int x;
            cin >> x;
            if (x == 5) {
                thermometers.push_back({i, j});
            } else if (x != 0) {
                heaters.push_back({{i, j}, x});
            }
        }
    }

    int W;
    cin >> W;
    for (int i = 0; i < W; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        if (c == 0) { // uw,dw
            uw[a][b] = true;
            dw[a - 1][b] = true;
        } else if (c == 1) { // lw,rw
            rw[a][b] = true;
            lw[a][b + 1] = true;
        }
    }

    cout << getResult(K) << endl;
    return 0;
}


