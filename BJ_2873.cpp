#include <iostream>
#include <string>

using namespace std;

int map[1001][1001];

string getResult(int N, int M) {
    string result;
    if (N % 2 != 0) {
        for (int i = 0; i < N; ++i) {
            char v = 'D', h;
            if (i % 2 == 0) {
                h = 'R';
            } else {
                h = 'L';
            }

            for (int j = 0; j < M - 1; ++j) {
                result += h;
            }

            if (i != N - 1)
                result += v;
        }
    } else if (M % 2 != 0) {
        for (int i = 0; i < M; ++i) {
            char v = 'R', h;
            if (i % 2 == 0) {
                h = 'D';
            } else {
                h = 'U';
            }

            for (int j = 0; j < N - 1; ++j) {
                result += h;
            }

            if (i != M - 1)
                result += v;
        }
    } else {
        int min = 10000;
        int mr = -1, mc = -1;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if ((i + j) % 2 != 0 && map[i][j] < min) {
                    min = map[i][j];
                    mr = i;
                    mc = j;
                }
            }
        }

        for (int i = 0; i < N; i += 2) {
            if (i == mr || i + 1 == mr) {
                //todo
                bool up = false;
                for (int j = 0; j < M - 1; j++) {
                    if (j == mc) {
                        result += "R";
                    } else if (up) {
                        result += "UR";
                        up = !up;
                    } else {
                        result += "DR";
                        up = !up;
                    }
                }

                if (up) {
                    if (i != N - 2) result += "D";
                }
                else {
                    if (i != N - 2) result += "DD";
                    else  result += "D";
                }
                //todo
            } else if (i < mr) {
                for (int j = 0; j < M - 1; ++j) {
                    result += 'R';
                }
                result += 'D';
                for (int j = 0; j < M - 1; ++j) {
                    result += 'L';
                }
                result += 'D';
            } else {
                for (int j = 0; j < M - 1; ++j) {
                    result += 'L';
                }
                result += 'D';
                for (int j = 0; j < M - 1; ++j) {
                    result += 'R';
                }
                if (i != N - 2)
                    result += 'D';
            }
        }
    }
    return result;
}


int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> map[i][j];
        }
    }

    cout << getResult(N, M) << endl;
    return 0;
}