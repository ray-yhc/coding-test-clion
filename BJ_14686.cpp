#include <iostream>
#include <vector>

using namespace std;

// nCr을 반환하는 함수
void combination(int n, int r, vector<int> combi, vector<vector<int>> &combiResult, int index, int depth){
    if (r == 0){
        combiResult.emplace_back(combi);
    } else if (depth == n) return;
    else {
        // depth를 뽑은 경우
        combi[index] = depth;
        combination(n, r - 1, combi, combiResult, index + 1, depth + 1);

        // depth를 제외한 경우
        combination(n, r, combi, combiResult, index, depth + 1);
    }
}

int getDist(int map[][50], int N, int x, int y) {

    for (int dist = 1; dist < N * 2; ++dist) {
        for (int dx = - dist; dx <= dist ; ++dx) {
            int dy = (dx > 0) ? dist - dx : dist + dx;

            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= N || ny < 0 || ny >= N);
            else if (map[ny][nx] == 2) return dist;

            // 음수일 경우
            if (dy != 0) {
                dy = -dy;
                nx = x + dx;
                ny = y + dy;
                if (nx < 0 || nx >= N || ny < 0 || ny >= N);
                else if (map[ny][nx] == 2) return dist;
            }
        }
    }
}


int chicken(int map[][50], int N, const vector<pair<int,int>>& bbq, int M){
    long long minDist = 9223372036854775806;

    vector<int> combi(M); // 길이 M인 빈 벡터 생성
    vector<vector<int>> combiResult; // 결과를 담을 벡터
    combination(bbq.size(), M, combi, combiResult, 0, 0);

    for (const vector<int>& openChickens : combiResult) {
        // 폐업 가게 고르기
        for (int index: openChickens) {
            int y = bbq[index].first;
            int x = bbq[index].second;
            map[y][x] = 2;
        }


        // 치킨거리 측정
        long long  dist = 0;
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (map[y][x] == 1) dist += getDist(map, N, x, y);
            }
        }
        minDist = min(minDist, dist);

        // 페업 원위치하기
        for (int index: openChickens) {
            int y = bbq[index].first;
            int x = bbq[index].second;
            map[y][x] = 0;
        }
    }
    return minDist;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int N,M;
    cin >> N >> M;

    int map[50][50]{0};
    vector<pair<int,int>> bbq;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                bbq.emplace_back(i, j);
                map[i][j] = 0;
            }
        }
    }
    cout << chicken(map, N, bbq, M) << endl;
    return 0;
}


//char initCube[6][3][3]{
//        // 0 : 윗면
//        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
//        // 1 : 아랫면
//        'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y',
//        // 2 : 앞
//        'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r',
//        // 3 : 뒤
//        'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
//        //4 : 왼
//        'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g',
//        // 5 : 오
//        'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b',
//};