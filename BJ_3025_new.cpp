#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

char gameMap[30001][31];
int N, M, D;
stack<pair<int, int>> checkpoint[31]; // checkpoint[col] == {row, col}
set<int> obstacles[31];


int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M ; ++j) {
            char cc;
            cin >> cc;
            gameMap[i][j] = cc;

            if (cc != '.') {
                obstacles[j].emplace(i);
            }
        }
    }

    cin >> D;
    for (int i = 0; i < D; ++i) {

        //
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