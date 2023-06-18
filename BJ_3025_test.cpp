#include <cstdio>
#include <vector>
#include <stack>
#include <set>

using namespace std;
using pii = pair<int, int>;

int r, c, q;
char b[30003][33], tmp[2];
set<int> top[33];
pii rec[33][30003];
int idx[33];


//origin : 최초에 어느 열에서 떨어뜨린건지
//row, col : 떨어뜨릴 돌의 현재 행과 열
void simulate(int row, int col, int origin) {
    // (row, col) 에서 떨어져 처음 부딪히는 가장 높은 빈칸의 높이
    int h = *(top[col].upper_bound(row));

    if (b[h][col] == 'O') {
        if (b[h][col - 1] == '.' && b[h - 1][col - 1] == '.') {
            rec[origin][idx[origin]] = {h - 1, col};
            idx[origin]++;
            simulate(h - 1, col - 1, origin);
        } else if (b[h][col + 1] == '.' && b[h - 1][col + 1] == '.') {
            rec[origin][idx[origin]] = {h - 1, col};
            idx[origin]++;
            simulate(h - 1, col + 1, origin);
        } else {
            b[h - 1][col] = 'O';
            top[col].erase(h);
            top[col].insert(h - 1);
        }
    } else {
        b[h - 1][col] = 'O';
        top[col].erase(h);
        top[col].insert(h - 1);
    }
}

void output() {
    for (int i = 1; i <= r; ++i)
        printf("%s\n", b[i] + 1);
}

int main() {
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            scanf("%1s", &tmp);
            b[i][j] = tmp[0];
            if (b[i][j] == 'X')
                top[j].insert(i);
        }
    }
    for (int i = 1; i <= c; ++i) {
        top[i].insert(r + 1);
    }

    scanf("%d", &q);
    while (q--) {
        int col;
        scanf("%d", &col);

        int r, c;
        while (idx[col] > 0) { // col열에서 떨어뜨린 돌의 체크포인트 개수
            r = rec[col][idx[col] - 1].first;
            c = rec[col][idx[col] - 1].second;
            if (b[r][c] != '.')
                --idx[col];
            else break;
        }
        if (idx[col] == 0) {   // '.'인 체크포인트가 없으면 처음부터 시뮬레이션
            simulate(1, col, col);
        } else {                 // '.'인 체크포인트가 있으면 그 지점에서부터 시뮬레이션
            simulate(r, c, col);
        }
    }
    output();
    return 0;
}