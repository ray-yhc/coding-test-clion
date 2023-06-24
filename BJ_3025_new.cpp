#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

char gameMap[30001][31];
int N, M, D;
stack<pair<int, int>> checkpoint[31]; // checkpoint[col] == {row, col}
set<int> obstacles[31];


void addStone(int r, int c) {
//    assert(gameMap[r][c] == '.');
    gameMap[r][c] = 'O';
    obstacles[c].emplace(r);
}

bool isEmpty(int r, int c) {
    if (r < 1 || r > N || c < 1 || c > M || gameMap[r][c] != '.') return false;
    return true;
}

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

int main() {

    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            char cc[2];
            scanf("%1s", &cc);
            gameMap[i][j] = cc[0];

            if (cc[0] != '.') {
                obstacles[j].emplace(i);
            }
        }
        getc(stdin);
    }


    scanf("%d", &D);
    for (int i = 0; i < D; ++i) {
        int dropColumn;
        scanf("%d", &dropColumn);

        // init
        int c = dropColumn;
        int r = 1;

        while (!checkpoint[dropColumn].empty()) {
            if (gameMap[checkpoint[dropColumn].top().first][checkpoint[dropColumn].top().second] != '.') {
                checkpoint[dropColumn].pop();
            } else {
                r = checkpoint[dropColumn].top().first;
                c = checkpoint[dropColumn].top().second;
                break;
            }
        }

        while (true) {
            if (obstacles[c].upper_bound(r) != obstacles[c].end()) {
                r = *(obstacles[c].upper_bound(r)) - 1;
            }
            else r = N;
//            assert(isEmpty(r, c));

            // X or end
            int nr = r + 1, nc = c;
            if (nr > N || gameMap[nr][nc] == 'X') {
                addStone(r, c);
                break;
            }

            //
            if (isEmpty(r, c - 1) && isEmpty(r + 1, c - 1)) {
                checkpoint[dropColumn].emplace(r, c);
                r = r + 1;
                c = c - 1;
            } else if (isEmpty(r, c + 1) && isEmpty(r + 1, c + 1)) {
                checkpoint[dropColumn].emplace(r, c);
                r = r + 1;
                c = c + 1;
            } else {
                addStone(r, c);
                break;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        printf("%s\n", gameMap[i] + 1);
    }

    return 0;
}

// 15 4
//....
//....
//X...
//.X..
//..X.
//....
//....
//...X
//..X.
//.X..
//....
//....
//X...
//.X..
//..X.
//10
//1
//1
//1
//1
//1
//1
//1
//1
//1
//1

