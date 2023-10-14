#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define pi pair<int,int>
#define pip pair<int, pair<int,int> >
using namespace std;

int M, N;
char A[100][100];
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

bool redIsFirst(pi red, pi blue, int d) {
    switch (d) {
        case 0:
            return red.second > blue.second;
        case 1:
            return red.first < blue.first;
        case 2:
            return red.second < blue.second;
        case 3:
            return red.first > blue.first;

    }
}

void printMap(pi red, pi blue) {
    cout << red.first << ' ' << red.second << ' ' << blue.first << ' ' << blue.second << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == red.first && j == red.second) cout << 'R';
            else if (i == blue.first && j == blue.second) cout << 'B';
            else cout << A[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int move(pi red, pi blue, int depth) {
//    printMap(red, blue);
    if (depth >= 10) return -1;

    int minMove = 1000000000;
    for (int d = 0; d < 4; ++d) {
//        cout << "depth:" << depth << " d:" << d << endl;
        pi tempRed(red);
        pi tempBlue(blue);
        bool blueOut = false;
        bool redOut = false;
        if (redIsFirst(red, blue, d)) {
            int r, c;
            // move red
            r = tempRed.first;
            c = tempRed.second;
            while (true) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (A[nr][nc] == 'O') {
                    redOut = true;
                    r = nr;
                    c = nc;
                    break;
                }
                if (A[nr][nc] == '#') break;
                if (tempBlue.first == nr && tempBlue.second == nc)break;
                r = nr;
                c = nc;
            }
            tempRed = pi(r, c);

            // move blue
            r = tempBlue.first;
            c = tempBlue.second;
            while (true) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (A[nr][nc] == 'O') {
                    blueOut = true;
                    r = nr;
                    c = nc;
                    break;
                }
                if (A[nr][nc] == '#') break;
                if (tempRed.first == nr && tempRed.second == nc)break;
                r = nr;
                c = nc;
            }
            tempBlue = pi(r, c);

        } else {
            int r, c;

            // move blue
            r = tempBlue.first;
            c = tempBlue.second;
            while (true) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (A[nr][nc] == 'O') {
                    blueOut = true;
                    r = nr;
                    c = nc;
                    break;
                }
                if (A[nr][nc] == '#') break;
                if (tempRed.first == nr && tempRed.second == nc)break;
                r = nr;
                c = nc;
            }
            tempBlue = pi(r, c);

            // move red
            r = tempRed.first;
            c = tempRed.second;
            while (!blueOut) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (A[nr][nc] == 'O') {
                    redOut = true;
                    r = nr;
                    c = nc;
                    break;
                }
                if (A[nr][nc] == '#') break;
                if (tempBlue.first == nr && tempBlue.second == nc)break;
                r = nr;
                c = nc;
            }
            tempRed = pi(r, c);
        }

//        cout << blueOut << ' ' << redOut << endl;
        if (blueOut) continue;
        if (redOut) return 1;
        if (red.first == tempRed.first && red.second == tempRed.second && blue.first == tempBlue.first &&
            blue.second == tempBlue.second)
            continue;
        int m = move(tempRed, tempBlue, depth + 1);
        if (m == -1) continue;
        minMove = min(minMove, m);
    }
    if (minMove == 1000000000) return -1;
    return minMove + 1;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);
    cin >> N >> M;
    pair<int, int> red, blue;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
            if (A[i][j] == 'B') {
                blue = pi(i, j);
                A[i][j] = '.';
            } else if (A[i][j] == 'R') {
                red = pi(i, j);
                A[i][j] = '.';
            }
        }
    }

    cout << move(red, blue, 0);

    return 0;
}