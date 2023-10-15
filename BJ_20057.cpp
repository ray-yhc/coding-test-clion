#include <iostream>
#include <vector>

using namespace std;


int N;
int A[500][500];
int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};

vector<vector<vector<int> > > spreadMap = {
        {
                {-1, 1,  1}, {1,  1,  1},
                {-1, 0,  7}, {1, 0, 7},
                {-2, 0,  2}, {2, 0, 2},
                {-1, -1, 10}, {1,  -1, 10},
                {0,  -2, 5}
        },
        {
                {-1, -1, 1}, {-1, 1,  1},
                {0,  -1, 7}, {0, 1, 7},
                {0,  -2, 2}, {0, 2, 2},
                {1,  -1, 10}, {1,  1,  10},
                {2,  0,  5}
        },
        {
                {-1, -1, 1}, {1,  -1, 1},
                {-1, 0,  7}, {1, 0, 7},
                {-2, 0,  2}, {2, 0, 2},
                {-1, 1,  10}, {1,  1,  10},
                {0,  2,  5}
        },
        {
                {1,  -1, 1}, {1,  1,  1},
                {0,  -1, 7}, {0, 1, 7},
                {0,  -2, 2}, {0, 2, 2},
                {-1, -1, 10}, {-1, 1,  10},
                {-2, 0,  5}
        }
};

int spread(int r, int c, int d) {
    int origin = A[r][c];
    if (origin == 0) return 0;

    int tempOrigin = origin;
    int out = 0;
    for (auto s: spreadMap[d]) {
        int nr = r + s[0];
        int nc = c + s[1];

        int amount = origin * s[2] / 100;

        if (amount == 0) continue;
        tempOrigin -= amount;
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
            out += amount;
        } else {
            A[nr][nc] += amount;
        }
    }
    int nr = r + dr[d];
    int nc = c + dc[d];
    if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
        out += tempOrigin;
    } else {
        A[nr][nc] += tempOrigin;
    }

    A[r][c] = 0;

    return out;
}


void printA() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void printA(int r, int c) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == r && j == c)cout << "SS\t";
            else
                cout << A[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    int r = N / 2, c = N / 2;
    int d = 0;
    int step = 1;
    int stepCount = 0;
    int totalOut = 0;

    while (r != 0 || c != 0) {
        // 모래 흩뿌리기
        r += dr[d];
        c += dc[d];
//        assert(!(r < 0 || r >= N || c < 0 || c >= N));

        totalOut += spread(r, c, d);
//        printA(r,c);

        // 이동하기
        stepCount++;
        if (stepCount == step) {
            stepCount = 0;
            d = (d == 3) ? 0 : d + 1;
            if (dr[d] == 0) step++;
        }

    }

    cout << totalOut << endl;

    return 0;
}