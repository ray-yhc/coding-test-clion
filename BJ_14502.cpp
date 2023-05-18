#include <iostream>
#include <queue>

using namespace std;



int doBFS(int map[][8], int N, int M){
    bool visited[8][8] = { false };

    // BFS 실행
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (map[i][j] == 1) {
                visited[i][j] = true;
            } else if (map[i][j] == 2 && !visited[i][j]) {
                visited[i][j] = true;

                int dx[]{1,0,-1,0};
                int dy[]{0,1,0,-1};
                queue<pair<int,int>> queue;
                queue.emplace(i, j);

                while (!queue.empty()) {
                    int y = queue.front().first;
                    int x = queue.front().second;
                    queue.pop();

                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d];
                        int nx = x + dx[d];

                        if (ny < 0 || ny >= N || nx < 0 || nx >= M)
                            continue;
                        if (visited[ny][nx] || map[ny][nx] == 1)
                            continue;
                        visited[ny][nx] = true;
                        queue.emplace(ny, nx);
                    }
                }
            }
        }
    }

    // 0 개수 세기
    int count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if(!visited[i][j]) count++;
        }
    }
    return count;
}

int safeZone(int map[][8], int N, int M){
    int maxSafe = 0;

    int c = 0;

    for (int i = 0; i < N * M; ++i) {
        for (int j = i + 1; j < N * M; ++j) {
            for (int k = j + 1; k < N * M; ++k) {
                if (i == j || j == k || k == i) continue;
                if (map[i / M][i % M] != 0 || map[j / M][j % M] != 0 || map[k / M][k % M] != 0) continue;

                c++;
                // 1 세개 세우기
                map[i / M][i % M] = 1;
                map[j / M][j % M] = 1;
                map[k / M][k % M] = 1;

                // BFS -> 안전지역 수 반환
                int safe = doBFS(map,N,M);
                maxSafe = max(safe, maxSafe);

                // 1 초기화하기
                map[i / M][i % M] = 0;
                map[j / M][j % M] = 0;
                map[k / M][k % M] = 0;
            }
        }
    }
//    cout<<c<<endl;

    return maxSafe;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int N,M;
    cin >> N >> M;

    int map[8][8];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> map[i][j];
        }
    }
    cout << safeZone(map, N, M) << endl;
    return 0;
}