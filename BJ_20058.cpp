#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int M;
int A[100][100];
bool visited[100][100];

void rotate(int r, int c, int dr, int dc) {
    int ta[100][100];
    fill(ta[0], ta[100], 0);

    for (int i = 0; i < dr; ++i) {
        for (int j = 0; j < dc; ++j) {
            ta[r + j][c + dc - 1 - i] = A[r + i][c + j];
        }
    }
    for (int i = 0; i < dr; ++i) {
        for (int j = 0; j < dc; ++j) {
            A[r + i][c + j] = ta[r + i][c + j];
        }
    }
}

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void melt() {
    int ta[100][100];
    fill(ta[0], ta[100], -1);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] == 0) continue;
            int cnt = 0;
            for (int d = 0; d < 4 && cnt < 2; ++d) {
                int nr = i + dr[d];
                int nc = j + dc[d];
                if (nr < 0 || nr >= M || nc < 0 || nc >= M) cnt++;
                else if (A[nr][nc] == 0) cnt++;
            }
            if (cnt >= 2) ta[i][j] = A[i][j] - 1;
        }
    }


    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (ta[i][j]==-1) continue;
            A[i][j] = ta[i][j];
        }
    }
}


int bfs(int r, int c) {
    queue<pair<int, int> > q;
    q.push({r, c});
    visited[r][c] = true;
    int cnt = 1;
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= M || nc < 0 || nc >= M) continue;
            if (visited[nr][nc])continue;
            visited[nr][nc] = true;
            if (A[nr][nc] == 0) continue;

            q.push({nr, nc});
            cnt++;
        }
    }

    return cnt;
};


void printA() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
//    freopen("./txts/1009.txt", "rt", stdin);
    int N, Q;
    cin >> N >> Q;
    M = 1 << N;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
        }
    }
    for (int q = 0; q < Q; ++q) {
        int l;
        cin >> l;

        if (l != 0) {
            int grid = 1 << (N - l);
            int width = 1 << l;
            for (int i = 0; i < grid; ++i) {
                for (int j = 0; j < grid; ++j) {
                    rotate(i * width, j * width, width, width);
                }
            }
        }
        melt();
//        printA();
    }

    int totalIce = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            totalIce += A[i][j];
        }
    }

    int cntMax = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (visited[i][j]) continue;
            if (A[i][j] != 0) {
                cntMax = max( cntMax, bfs(i, j));
            }
        }
    }
    cout << totalIce << endl << cntMax << endl;
    return 0;
}