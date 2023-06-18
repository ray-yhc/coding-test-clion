#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

char gameMap[30001][31];
int N, M, D;

stack<pair<int, int>> checkpoint[31]; // checkpoint[col] == {row, col}
set<int> obstacles[31];

int totalIter = 0, stackCRUD = 0;
void printStat(){
    cout << "totalIter : " << totalIter << endl;
    cout << "stackCRUD : " << stackCRUD << endl;
}


bool isEmpty(int r, int c) {
    if (r <= 0 || r > N || c <= 0 || c > M) return false;
    return gameMap[r][c] == '.';
}

int stNUm = 0;

void addStone(int r, int c) {
//    assert(!(r <= 0 || r > N || c <= 0 || c > M) && gameMap[r][c] == '.');
//    gameMap[r][c] = '0' + (stNUm++);
    gameMap[r][c] = 'O';
    obstacles[c].emplace(r);
}

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

int main() {
    cin >> N >> M;

    char ch;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> ch;
            gameMap[i][j] = ch;
            if (ch != '.')
                obstacles[j].emplace(i);
        }
    }

    cin >> D;
    for (int i = 0; i < D; ++i) {
        int dropColumn;
        cin >> dropColumn;

        if (!isEmpty(1, dropColumn)) {
            continue;
        }

        // trim checkpoint
        while (!checkpoint[dropColumn].empty()) {
            int nr = checkpoint[dropColumn].top().first;
            int nc = checkpoint[dropColumn].top().second;
            if (gameMap[nr][nc] != '.') {
                stackCRUD++; //todo
                totalIter++; //todo
                checkpoint[dropColumn].pop();
            }
            else break;
        }

        int c,r;
        if (checkpoint[dropColumn].empty()) {
            c = dropColumn;
            r = (obstacles[c].upper_bound(1) == obstacles[c].end())?
                    N : *(obstacles[c].upper_bound(1)) - 1;
        } else {
            r = checkpoint[dropColumn].top().first;
            c = checkpoint[dropColumn].top().second;
        }

        while(true) {
            totalIter++; //todo
            // r+1이 벽이거나 out인 경우,
            int nr = r + 1, nc = c;
            if (nr <= 0 || nr > N || nc <= 0 || nc > M
                || gameMap[nr][nc] == 'X') {
                addStone(r, c);
                break;
            }

            // r+1이 돌인 경우
//            assert(gameMap[nr][nc] != '.');
            // 좌측 (r,c-1) (r+1, c-1) 진입가능
            if (isEmpty(r, c - 1) && isEmpty(r + 1, c - 1)) {
                // add checkpoint
                checkpoint[dropColumn].emplace(r, c);
                stackCRUD++; //todo

                c = c - 1;
                r = (obstacles[c].upper_bound(r+1) == obstacles[c].end())?
                    N : *(obstacles[c].upper_bound(r+1)) - 1;

            }
            // 우측 (r,c+1) (r+1, c+1) 진입가능
            else if (isEmpty(r, c + 1) && isEmpty(r + 1, c + 1)) {
                // add checkpoint
                checkpoint[dropColumn].emplace(r, c);
                stackCRUD++; //todo

                c = c + 1;
                r = (obstacles[c].upper_bound(r+1) == obstacles[c].end())?
                    N : *(obstacles[c].upper_bound(r+1)) - 1;
            }
            else { // 진입 불가능
                addStone(r, c);
                break;
            }
        }
    }


    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cout << gameMap[i][j];
        }
        cout << endl;
    }

    printStat(); //todo

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